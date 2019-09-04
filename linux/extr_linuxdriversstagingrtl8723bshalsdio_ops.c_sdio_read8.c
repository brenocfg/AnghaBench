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
typedef  int /*<<< orphan*/  u32 ;
struct intf_hdl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cvrt2ftaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_read8 (struct intf_hdl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 sdio_read8(struct intf_hdl *intfhdl, u32 addr)
{
	u32 ftaddr;
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);

	return sd_read8(intfhdl, ftaddr, NULL);
}