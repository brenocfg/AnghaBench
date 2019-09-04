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
typedef  scalar_t__ u16 ;
struct quatech_feature {scalar_t__ devid; int amcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 struct quatech_feature* quatech_cards ; 

__attribute__((used)) static int pci_quatech_amcc(u16 devid)
{
	struct quatech_feature *qf = &quatech_cards[0];
	while (qf->devid) {
		if (qf->devid == devid)
			return qf->amcc;
		qf++;
	}
	pr_err("quatech: unknown port type '0x%04X'.\n", devid);
	return 0;
}