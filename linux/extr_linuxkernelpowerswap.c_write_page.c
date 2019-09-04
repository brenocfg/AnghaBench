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
struct hib_bio_batch {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int ENOSPC ; 
 int GFP_NOIO ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  REQ_SYNC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 scalar_t__ __get_free_page (int) ; 
 int /*<<< orphan*/  copy_page (void*,void*) ; 
 int hib_submit_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct hib_bio_batch*) ; 
 int hib_wait_io (struct hib_bio_batch*) ; 

__attribute__((used)) static int write_page(void *buf, sector_t offset, struct hib_bio_batch *hb)
{
	void *src;
	int ret;

	if (!offset)
		return -ENOSPC;

	if (hb) {
		src = (void *)__get_free_page(GFP_NOIO | __GFP_NOWARN |
		                              __GFP_NORETRY);
		if (src) {
			copy_page(src, buf);
		} else {
			ret = hib_wait_io(hb); /* Free pages */
			if (ret)
				return ret;
			src = (void *)__get_free_page(GFP_NOIO |
			                              __GFP_NOWARN |
			                              __GFP_NORETRY);
			if (src) {
				copy_page(src, buf);
			} else {
				WARN_ON_ONCE(1);
				hb = NULL;	/* Go synchronous */
				src = buf;
			}
		}
	} else {
		src = buf;
	}
	return hib_submit_io(REQ_OP_WRITE, REQ_SYNC, offset, src, hb);
}