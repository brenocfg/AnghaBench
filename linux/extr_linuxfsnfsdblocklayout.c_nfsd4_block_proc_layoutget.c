#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct svc_fh {int dummy; } ;
struct super_block {TYPE_1__* s_export_op; } ;
struct pnfs_block_extent {int foff; scalar_t__ len; int /*<<< orphan*/  es; int /*<<< orphan*/  vol_id; int /*<<< orphan*/  soff; } ;
struct nfsd4_layout_seg {int offset; scalar_t__ length; scalar_t__ iomode; } ;
struct nfsd4_layoutget {scalar_t__ lg_minlength; struct pnfs_block_extent* lg_content; struct nfsd4_layout_seg lg_seg; } ;
struct iomap {scalar_t__ length; int type; int offset; int /*<<< orphan*/  addr; } ;
struct inode {struct super_block* i_sb; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int (* map_blocks ) (struct inode*,int,scalar_t__,struct iomap*,int,int*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IOMAP_DELALLOC 131 
#define  IOMAP_HOLE 130 
#define  IOMAP_MAPPED 129 
#define  IOMAP_UNWRITTEN 128 
 scalar_t__ IOMODE_READ ; 
 int IOMODE_RW ; 
 int /*<<< orphan*/  PNFS_BLOCK_INVALID_DATA ; 
 int /*<<< orphan*/  PNFS_BLOCK_NONE_DATA ; 
 int /*<<< orphan*/  PNFS_BLOCK_READWRITE_DATA ; 
 int /*<<< orphan*/  PNFS_BLOCK_READ_DATA ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int i_blocksize (struct inode*) ; 
 struct pnfs_block_extent* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nfsd4_set_deviceid (int /*<<< orphan*/ *,struct svc_fh const*,int) ; 
 int /*<<< orphan*/  nfserr_layoutunavailable ; 
 int /*<<< orphan*/  nfserrno (int) ; 
 int stub1 (struct inode*,int,scalar_t__,struct iomap*,int,int*) ; 

__attribute__((used)) static __be32
nfsd4_block_proc_layoutget(struct inode *inode, const struct svc_fh *fhp,
		struct nfsd4_layoutget *args)
{
	struct nfsd4_layout_seg *seg = &args->lg_seg;
	struct super_block *sb = inode->i_sb;
	u32 block_size = i_blocksize(inode);
	struct pnfs_block_extent *bex;
	struct iomap iomap;
	u32 device_generation = 0;
	int error;

	if (seg->offset & (block_size - 1)) {
		dprintk("pnfsd: I/O misaligned\n");
		goto out_layoutunavailable;
	}

	/*
	 * Some clients barf on non-zero block numbers for NONE or INVALID
	 * layouts, so make sure to zero the whole structure.
	 */
	error = -ENOMEM;
	bex = kzalloc(sizeof(*bex), GFP_KERNEL);
	if (!bex)
		goto out_error;
	args->lg_content = bex;

	error = sb->s_export_op->map_blocks(inode, seg->offset, seg->length,
					    &iomap, seg->iomode != IOMODE_READ,
					    &device_generation);
	if (error) {
		if (error == -ENXIO)
			goto out_layoutunavailable;
		goto out_error;
	}

	if (iomap.length < args->lg_minlength) {
		dprintk("pnfsd: extent smaller than minlength\n");
		goto out_layoutunavailable;
	}

	switch (iomap.type) {
	case IOMAP_MAPPED:
		if (seg->iomode == IOMODE_READ)
			bex->es = PNFS_BLOCK_READ_DATA;
		else
			bex->es = PNFS_BLOCK_READWRITE_DATA;
		bex->soff = iomap.addr;
		break;
	case IOMAP_UNWRITTEN:
		if (seg->iomode & IOMODE_RW) {
			/*
			 * Crack monkey special case from section 2.3.1.
			 */
			if (args->lg_minlength == 0) {
				dprintk("pnfsd: no soup for you!\n");
				goto out_layoutunavailable;
			}

			bex->es = PNFS_BLOCK_INVALID_DATA;
			bex->soff = iomap.addr;
			break;
		}
		/*FALLTHRU*/
	case IOMAP_HOLE:
		if (seg->iomode == IOMODE_READ) {
			bex->es = PNFS_BLOCK_NONE_DATA;
			break;
		}
		/*FALLTHRU*/
	case IOMAP_DELALLOC:
	default:
		WARN(1, "pnfsd: filesystem returned %d extent\n", iomap.type);
		goto out_layoutunavailable;
	}

	error = nfsd4_set_deviceid(&bex->vol_id, fhp, device_generation);
	if (error)
		goto out_error;
	bex->foff = iomap.offset;
	bex->len = iomap.length;

	seg->offset = iomap.offset;
	seg->length = iomap.length;

	dprintk("GET: 0x%llx:0x%llx %d\n", bex->foff, bex->len, bex->es);
	return 0;

out_error:
	seg->length = 0;
	return nfserrno(error);
out_layoutunavailable:
	seg->length = 0;
	return nfserr_layoutunavailable;
}