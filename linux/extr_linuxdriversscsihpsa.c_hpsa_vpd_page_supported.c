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
typedef  unsigned char u8 ;
struct ctlr_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HPSA_VPD_HEADER_SZ ; 
 int HPSA_VPD_SUPPORTED_PAGES ; 
 int VPD_PAGE ; 
 int hpsa_scsi_do_inquiry (struct ctlr_info*,unsigned char*,int,unsigned char*,unsigned char) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hpsa_vpd_page_supported(struct ctlr_info *h,
	unsigned char scsi3addr[], u8 page)
{
	int rc;
	int i;
	int pages;
	unsigned char *buf, bufsize;

	buf = kzalloc(256, GFP_KERNEL);
	if (!buf)
		return false;

	/* Get the size of the page list first */
	rc = hpsa_scsi_do_inquiry(h, scsi3addr,
				VPD_PAGE | HPSA_VPD_SUPPORTED_PAGES,
				buf, HPSA_VPD_HEADER_SZ);
	if (rc != 0)
		goto exit_unsupported;
	pages = buf[3];
	if ((pages + HPSA_VPD_HEADER_SZ) <= 255)
		bufsize = pages + HPSA_VPD_HEADER_SZ;
	else
		bufsize = 255;

	/* Get the whole VPD page list */
	rc = hpsa_scsi_do_inquiry(h, scsi3addr,
				VPD_PAGE | HPSA_VPD_SUPPORTED_PAGES,
				buf, bufsize);
	if (rc != 0)
		goto exit_unsupported;

	pages = buf[3];
	for (i = 1; i <= pages; i++)
		if (buf[3 + i] == page)
			goto exit_supported;
exit_unsupported:
	kfree(buf);
	return false;
exit_supported:
	kfree(buf);
	return true;
}