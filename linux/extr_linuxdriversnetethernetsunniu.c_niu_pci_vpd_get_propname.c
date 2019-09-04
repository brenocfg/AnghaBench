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
typedef  scalar_t__ u32 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int niu_pci_eeprom_read (struct niu*,scalar_t__) ; 

__attribute__((used)) static int niu_pci_vpd_get_propname(struct niu *np, u32 off, char *namebuf,
				    int namebuf_len)
{
	int i;

	for (i = 0; i < namebuf_len; i++) {
		int err = niu_pci_eeprom_read(np, off + i);
		if (err < 0)
			return err;
		*namebuf++ = err;
		if (!err)
			break;
	}
	if (i >= namebuf_len)
		return -EINVAL;

	return i + 1;
}