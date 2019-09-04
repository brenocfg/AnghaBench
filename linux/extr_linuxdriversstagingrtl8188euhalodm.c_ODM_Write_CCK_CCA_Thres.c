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
typedef  scalar_t__ u8 ;
struct rtw_dig {scalar_t__ CurCCK_CCAThres; scalar_t__ PreCCK_CCAThres; } ;
struct odm_dm_struct {struct adapter* Adapter; struct rtw_dig DM_DigTable; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_REG_CCK_CCA_11N ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,scalar_t__) ; 

void ODM_Write_CCK_CCA_Thres(struct odm_dm_struct *pDM_Odm, u8 CurCCK_CCAThres)
{
	struct rtw_dig *pDM_DigTable = &pDM_Odm->DM_DigTable;
	struct adapter *adapt = pDM_Odm->Adapter;

	if (pDM_DigTable->CurCCK_CCAThres != CurCCK_CCAThres)		/* modify by Guo.Mingzhi 2012-01-03 */
		usb_write8(adapt, ODM_REG_CCK_CCA_11N, CurCCK_CCAThres);
	pDM_DigTable->PreCCK_CCAThres = pDM_DigTable->CurCCK_CCAThres;
	pDM_DigTable->CurCCK_CCAThres = CurCCK_CCAThres;
}