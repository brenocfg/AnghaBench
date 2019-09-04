#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pnfs_block_volume {int type; } ;
struct pnfs_block_dev {int dummy; } ;
struct nfs_server {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EIO ; 
#define  PNFS_BLOCK_VOLUME_CONCAT 132 
#define  PNFS_BLOCK_VOLUME_SCSI 131 
#define  PNFS_BLOCK_VOLUME_SIMPLE 130 
#define  PNFS_BLOCK_VOLUME_SLICE 129 
#define  PNFS_BLOCK_VOLUME_STRIPE 128 
 int bl_parse_concat (struct nfs_server*,struct pnfs_block_dev*,struct pnfs_block_volume*,int,int /*<<< orphan*/ ) ; 
 int bl_parse_scsi (struct nfs_server*,struct pnfs_block_dev*,struct pnfs_block_volume*,int,int /*<<< orphan*/ ) ; 
 int bl_parse_simple (struct nfs_server*,struct pnfs_block_dev*,struct pnfs_block_volume*,int,int /*<<< orphan*/ ) ; 
 int bl_parse_slice (struct nfs_server*,struct pnfs_block_dev*,struct pnfs_block_volume*,int,int /*<<< orphan*/ ) ; 
 int bl_parse_stripe (struct nfs_server*,struct pnfs_block_dev*,struct pnfs_block_volume*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int
bl_parse_deviceid(struct nfs_server *server, struct pnfs_block_dev *d,
		struct pnfs_block_volume *volumes, int idx, gfp_t gfp_mask)
{
	switch (volumes[idx].type) {
	case PNFS_BLOCK_VOLUME_SIMPLE:
		return bl_parse_simple(server, d, volumes, idx, gfp_mask);
	case PNFS_BLOCK_VOLUME_SLICE:
		return bl_parse_slice(server, d, volumes, idx, gfp_mask);
	case PNFS_BLOCK_VOLUME_CONCAT:
		return bl_parse_concat(server, d, volumes, idx, gfp_mask);
	case PNFS_BLOCK_VOLUME_STRIPE:
		return bl_parse_stripe(server, d, volumes, idx, gfp_mask);
	case PNFS_BLOCK_VOLUME_SCSI:
		return bl_parse_scsi(server, d, volumes, idx, gfp_mask);
	default:
		dprintk("unsupported volume type: %d\n", volumes[idx].type);
		return -EIO;
	}
}