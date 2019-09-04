#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct intf_hdl {int dummy; } ;
struct TYPE_2__ {struct intf_hdl intf; } ;
struct adapter {TYPE_1__ iopriv; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  HalSdioGetCmdAddr8723BSdio (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDIO_LOCAL_DEVICE_ID ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  sd_cmd52_read (struct intf_hdl*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 SdioLocalCmd52Read2Byte(struct adapter *adapter, u32 addr)
{
	__le16 val = 0;
	struct intf_hdl *intfhdl = &adapter->iopriv.intf;

	HalSdioGetCmdAddr8723BSdio(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	sd_cmd52_read(intfhdl, addr, 2, (u8 *)&val);

	return le16_to_cpu(val);
}