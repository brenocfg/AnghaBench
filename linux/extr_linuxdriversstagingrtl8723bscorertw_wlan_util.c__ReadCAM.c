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
struct adapter {int dummy; } ;

/* Variables and functions */
 int CAM_POLLINIG ; 
 int /*<<< orphan*/  REG_CAMCMD ; 
 int /*<<< orphan*/  REG_CAMREAD ; 
 int /*<<< orphan*/  RWCAM ; 
 int rtw_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 _ReadCAM(struct adapter *padapter, u32 addr)
{
	u32 count = 0, cmd;
	cmd = CAM_POLLINIG | addr;
	rtw_write32(padapter, RWCAM, cmd);

	do {
		if (0 == (rtw_read32(padapter, REG_CAMCMD) & CAM_POLLINIG))
			break;
	} while (count++ < 100);

	return rtw_read32(padapter, REG_CAMREAD);
}