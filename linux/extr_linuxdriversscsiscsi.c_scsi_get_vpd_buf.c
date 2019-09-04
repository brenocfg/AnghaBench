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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_vpd {int len; int /*<<< orphan*/  data; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SCSI_VPD_PG_LEN ; 
 int /*<<< orphan*/  kfree (struct scsi_vpd*) ; 
 struct scsi_vpd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int scsi_vpd_inquiry (struct scsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct scsi_vpd *scsi_get_vpd_buf(struct scsi_device *sdev, u8 page)
{
	struct scsi_vpd *vpd_buf;
	int vpd_len = SCSI_VPD_PG_LEN, result;

retry_pg:
	vpd_buf = kmalloc(sizeof(*vpd_buf) + vpd_len, GFP_KERNEL);
	if (!vpd_buf)
		return NULL;

	result = scsi_vpd_inquiry(sdev, vpd_buf->data, page, vpd_len);
	if (result < 0) {
		kfree(vpd_buf);
		return NULL;
	}
	if (result > vpd_len) {
		vpd_len = result;
		kfree(vpd_buf);
		goto retry_pg;
	}

	vpd_buf->len = result;

	return vpd_buf;
}