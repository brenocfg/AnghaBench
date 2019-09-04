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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 

__attribute__((used)) static u16 b43legacy_get_txgain_dac(u16 txpower)
{
	u16 ret;

	B43legacy_WARN_ON(txpower > 63);

	if (txpower >= 54)
		ret = txpower - 53;
	else if (txpower >= 49)
		ret = txpower - 42;
	else if (txpower >= 44)
		ret = txpower - 37;
	else if (txpower >= 32)
		ret = txpower - 32;
	else if (txpower >= 25)
		ret = txpower - 20;
	else if (txpower >= 20)
		ret = txpower - 13;
	else if (txpower >= 12)
		ret = txpower - 8;
	else
		ret = txpower;

	return ret;
}