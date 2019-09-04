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
typedef  int u64 ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_truncate_size; int /*<<< orphan*/  i_truncate_seq; int /*<<< orphan*/  i_layout; } ;
struct ceph_fs_client {TYPE_1__* client; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  osdc; } ;

/* Variables and functions */
 int CHECK_EOF ; 
 int ENOENT ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 int ceph_osdc_readpages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page**,int,int) ; 
 int /*<<< orphan*/  ceph_vino (struct inode*) ; 
 int /*<<< orphan*/  ceph_zero_page_vector_range (int,int,struct page**) ; 
 int /*<<< orphan*/  dout (char*,int,...) ; 
 int i_size_read (struct inode*) ; 
 int min (int,int) ; 

__attribute__((used)) static int striped_read(struct inode *inode,
			u64 pos, u64 len,
			struct page **pages, int num_pages,
			int page_align, int *checkeof)
{
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	struct ceph_inode_info *ci = ceph_inode(inode);
	u64 this_len;
	loff_t i_size;
	int page_idx;
	int ret, read = 0;
	bool hit_stripe, was_short;

	/*
	 * we may need to do multiple reads.  not atomic, unfortunately.
	 */
more:
	this_len = len;
	page_idx = (page_align + read) >> PAGE_SHIFT;
	ret = ceph_osdc_readpages(&fsc->client->osdc, ceph_vino(inode),
				  &ci->i_layout, pos, &this_len,
				  ci->i_truncate_seq, ci->i_truncate_size,
				  pages + page_idx, num_pages - page_idx,
				  ((page_align + read) & ~PAGE_MASK));
	if (ret == -ENOENT)
		ret = 0;
	hit_stripe = this_len < len;
	was_short = ret >= 0 && ret < this_len;
	dout("striped_read %llu~%llu (read %u) got %d%s%s\n", pos, len, read,
	     ret, hit_stripe ? " HITSTRIPE" : "", was_short ? " SHORT" : "");

	i_size = i_size_read(inode);
	if (ret >= 0) {
		if (was_short && (pos + ret < i_size)) {
			int zlen = min(this_len - ret, i_size - pos - ret);
			int zoff = page_align + read + ret;
			dout(" zero gap %llu to %llu\n",
			     pos + ret, pos + ret + zlen);
			ceph_zero_page_vector_range(zoff, zlen, pages);
			ret += zlen;
		}

		read += ret;
		pos += ret;
		len -= ret;

		/* hit stripe and need continue*/
		if (len && hit_stripe && pos < i_size)
			goto more;
	}

	if (read > 0) {
		ret = read;
		/* did we bounce off eof? */
		if (pos + len > i_size)
			*checkeof = CHECK_EOF;
	}

	dout("striped_read returns %d\n", ret);
	return ret;
}