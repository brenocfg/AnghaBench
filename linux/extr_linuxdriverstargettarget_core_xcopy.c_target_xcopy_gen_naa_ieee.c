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
struct se_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spc_parse_naa_6h_vendor_specific (struct se_device*,unsigned char*) ; 

__attribute__((used)) static int target_xcopy_gen_naa_ieee(struct se_device *dev, unsigned char *buf)
{
	int off = 0;

	buf[off++] = (0x6 << 4);
	buf[off++] = 0x01;
	buf[off++] = 0x40;
	buf[off] = (0x5 << 4);

	spc_parse_naa_6h_vendor_specific(dev, &buf[off]);
	return 0;
}