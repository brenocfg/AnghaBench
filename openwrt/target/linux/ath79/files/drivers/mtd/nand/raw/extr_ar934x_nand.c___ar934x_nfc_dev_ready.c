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
typedef  int u32 ;
struct ar934x_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR934X_NFC_REG_STATUS ; 
 int ar934x_nfc_rr (struct ar934x_nfc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __ar934x_nfc_dev_ready(struct ar934x_nfc *nfc)
{
	u32 status;

	status = ar934x_nfc_rr(nfc, AR934X_NFC_REG_STATUS);
	return (status & 0xff) == 0xff;
}