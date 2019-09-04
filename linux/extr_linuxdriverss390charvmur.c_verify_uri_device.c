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
struct TYPE_2__ {int /*<<< orphan*/  devno; } ;
struct urdev {TYPE_1__ dev_id; } ;
struct file_control_block {int file_stat; } ;

/* Variables and functions */
 int EMFILE ; 
 int ENODATA ; 
 int ENOMEM ; 
 int EPERM ; 
 int FLG_IN_USE ; 
 int FLG_SYSTEM_HOLD ; 
 int FLG_USER_HOLD ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ __get_free_page (int) ; 
 int diag_read_file (int /*<<< orphan*/ ,char*) ; 
 int diag_read_next_file_info (struct file_control_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct file_control_block*) ; 
 struct file_control_block* kmalloc (int,int) ; 

__attribute__((used)) static int verify_uri_device(struct urdev *urd)
{
	struct file_control_block *fcb;
	char *buf;
	int rc;

	fcb = kmalloc(sizeof(*fcb), GFP_KERNEL | GFP_DMA);
	if (!fcb)
		return -ENOMEM;

	/* check for empty reader device (beginning of chain) */
	rc = diag_read_next_file_info(fcb, 0);
	if (rc)
		goto fail_free_fcb;

	/* if file is in hold status, we do not read it */
	if (fcb->file_stat & (FLG_SYSTEM_HOLD | FLG_USER_HOLD)) {
		rc = -EPERM;
		goto fail_free_fcb;
	}

	/* open file on virtual reader	*/
	buf = (char *) __get_free_page(GFP_KERNEL | GFP_DMA);
	if (!buf) {
		rc = -ENOMEM;
		goto fail_free_fcb;
	}
	rc = diag_read_file(urd->dev_id.devno, buf);
	if ((rc != 0) && (rc != -ENODATA)) /* EOF does not hurt */
		goto fail_free_buf;

	/* check if the file on top of the queue is open now */
	rc = diag_read_next_file_info(fcb, 0);
	if (rc)
		goto fail_free_buf;
	if (!(fcb->file_stat & FLG_IN_USE)) {
		rc = -EMFILE;
		goto fail_free_buf;
	}
	rc = 0;

fail_free_buf:
	free_page((unsigned long) buf);
fail_free_fcb:
	kfree(fcb);
	return rc;
}