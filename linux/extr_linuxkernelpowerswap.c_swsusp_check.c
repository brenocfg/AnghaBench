#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  orig_sig; int /*<<< orphan*/  sig; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  HIBERNATE_SIG ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  REQ_SYNC ; 
 int /*<<< orphan*/  blkdev_get_by_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_page (TYPE_1__*) ; 
 int /*<<< orphan*/  hib_resume_bdev ; 
 int hib_submit_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  set_blocksize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* swsusp_header ; 
 int /*<<< orphan*/  swsusp_resume_block ; 
 int /*<<< orphan*/  swsusp_resume_device ; 

int swsusp_check(void)
{
	int error;

	hib_resume_bdev = blkdev_get_by_dev(swsusp_resume_device,
					    FMODE_READ, NULL);
	if (!IS_ERR(hib_resume_bdev)) {
		set_blocksize(hib_resume_bdev, PAGE_SIZE);
		clear_page(swsusp_header);
		error = hib_submit_io(REQ_OP_READ, 0,
					swsusp_resume_block,
					swsusp_header, NULL);
		if (error)
			goto put;

		if (!memcmp(HIBERNATE_SIG, swsusp_header->sig, 10)) {
			memcpy(swsusp_header->sig, swsusp_header->orig_sig, 10);
			/* Reset swap signature now */
			error = hib_submit_io(REQ_OP_WRITE, REQ_SYNC,
						swsusp_resume_block,
						swsusp_header, NULL);
		} else {
			error = -EINVAL;
		}

put:
		if (error)
			blkdev_put(hib_resume_bdev, FMODE_READ);
		else
			pr_debug("Image signature found, resuming\n");
	} else {
		error = PTR_ERR(hib_resume_bdev);
	}

	if (error)
		pr_debug("Image not found (code %d)\n", error);

	return error;
}