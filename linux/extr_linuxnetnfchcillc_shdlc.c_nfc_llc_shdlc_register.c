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
 int /*<<< orphan*/  LLC_SHDLC_NAME ; 
 int /*<<< orphan*/  llc_shdlc_ops ; 
 int nfc_llc_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nfc_llc_shdlc_register(void)
{
	return nfc_llc_register(LLC_SHDLC_NAME, &llc_shdlc_ops);
}