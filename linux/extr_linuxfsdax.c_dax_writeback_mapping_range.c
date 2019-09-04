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
struct writeback_control {scalar_t__ sync_mode; int range_start; int range_end; } ;
struct pagevec {int nr; int /*<<< orphan*/ * pages; } ;
struct inode {int i_blkbits; } ;
struct dax_device {int dummy; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct address_space {int /*<<< orphan*/  nrexceptional; struct inode* host; } ;
typedef  int pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PAGECACHE_TAG_TOWRITE ; 
 int PAGEVEC_SIZE ; 
 int PAGE_SHIFT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ WB_SYNC_ALL ; 
 struct dax_device* dax_get_by_host (int /*<<< orphan*/ ) ; 
 int dax_writeback_one (struct dax_device*,struct address_space*,int,int /*<<< orphan*/ ) ; 
 int find_get_entries_tag (struct address_space*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mapping_set_error (struct address_space*,int) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int /*<<< orphan*/  put_dax (struct dax_device*) ; 
 int /*<<< orphan*/  tag_pages_for_writeback (struct address_space*,int,int) ; 
 int /*<<< orphan*/  trace_dax_writeback_range (struct inode*,int,int) ; 
 int /*<<< orphan*/  trace_dax_writeback_range_done (struct inode*,int,int) ; 

int dax_writeback_mapping_range(struct address_space *mapping,
		struct block_device *bdev, struct writeback_control *wbc)
{
	struct inode *inode = mapping->host;
	pgoff_t start_index, end_index;
	pgoff_t indices[PAGEVEC_SIZE];
	struct dax_device *dax_dev;
	struct pagevec pvec;
	bool done = false;
	int i, ret = 0;

	if (WARN_ON_ONCE(inode->i_blkbits != PAGE_SHIFT))
		return -EIO;

	if (!mapping->nrexceptional || wbc->sync_mode != WB_SYNC_ALL)
		return 0;

	dax_dev = dax_get_by_host(bdev->bd_disk->disk_name);
	if (!dax_dev)
		return -EIO;

	start_index = wbc->range_start >> PAGE_SHIFT;
	end_index = wbc->range_end >> PAGE_SHIFT;

	trace_dax_writeback_range(inode, start_index, end_index);

	tag_pages_for_writeback(mapping, start_index, end_index);

	pagevec_init(&pvec);
	while (!done) {
		pvec.nr = find_get_entries_tag(mapping, start_index,
				PAGECACHE_TAG_TOWRITE, PAGEVEC_SIZE,
				pvec.pages, indices);

		if (pvec.nr == 0)
			break;

		for (i = 0; i < pvec.nr; i++) {
			if (indices[i] > end_index) {
				done = true;
				break;
			}

			ret = dax_writeback_one(dax_dev, mapping, indices[i],
					pvec.pages[i]);
			if (ret < 0) {
				mapping_set_error(mapping, ret);
				goto out;
			}
		}
		start_index = indices[pvec.nr - 1] + 1;
	}
out:
	put_dax(dax_dev);
	trace_dax_writeback_range_done(inode, start_index, end_index);
	return (ret < 0 ? ret : 0);
}