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

/* Variables and functions */
 int /*<<< orphan*/  nfc_llc_exit () ; 
 int nfc_llc_nop_register () ; 
 int nfc_llc_shdlc_register () ; 

int nfc_llc_init(void)
{
	int r;

	r = nfc_llc_nop_register();
	if (r)
		goto exit;

	r = nfc_llc_shdlc_register();
	if (r)
		goto exit;

	return 0;

exit:
	nfc_llc_exit();
	return r;
}