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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RX_DRVINFO_SZ ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _InitDriverInfoSize(struct adapter *Adapter, u8 drvInfoSize)
{
	usb_write8(Adapter, REG_RX_DRVINFO_SZ, drvInfoSize);
}