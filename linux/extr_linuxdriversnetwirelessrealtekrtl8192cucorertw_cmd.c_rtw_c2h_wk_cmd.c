#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct drvextra_cmd_parm {int type_size; int /*<<< orphan*/ * pbuf; int /*<<< orphan*/  ec_id; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__* PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  C2H_WK_CID ; 
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _Set_Drv_Extra ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct drvextra_cmd_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_c2h_wk_cmd(PADAPTER padapter, u8 *c2h_evt)
{
	struct cmd_obj *ph2c;
	struct drvextra_cmd_parm *pdrvextra_cmd_parm;
	struct cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	u8	res = _SUCCESS;

	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if (ph2c == NULL) {
		res = _FAIL;
		goto exit;
	}

	pdrvextra_cmd_parm = (struct drvextra_cmd_parm*)rtw_zmalloc(sizeof(struct drvextra_cmd_parm));
	if (pdrvextra_cmd_parm == NULL) {
		rtw_mfree((u8*)ph2c, sizeof(struct cmd_obj));
		res = _FAIL;
		goto exit;
	}

	pdrvextra_cmd_parm->ec_id = C2H_WK_CID;
	pdrvextra_cmd_parm->type_size = c2h_evt?16:0;
	pdrvextra_cmd_parm->pbuf = c2h_evt;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, GEN_CMD_CODE(_Set_Drv_Extra));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	
exit:
	
	return res;
}