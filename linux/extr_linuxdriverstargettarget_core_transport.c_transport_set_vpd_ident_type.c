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
struct t10_vpd {unsigned char device_identifier_type; } ;

/* Variables and functions */
 int transport_dump_vpd_ident_type (struct t10_vpd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int transport_set_vpd_ident_type(struct t10_vpd *vpd, unsigned char *page_83)
{
	/*
	 * The VPD identifier type..
	 *
	 * from spc3r23.pdf Section 7.6.3.1 Table 298
	 */
	vpd->device_identifier_type = (page_83[1] & 0x0f);
	return transport_dump_vpd_ident_type(vpd, NULL, 0);
}