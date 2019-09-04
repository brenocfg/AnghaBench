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
struct set_assocsta_rsp {int dummy; } ;
struct set_assocsta_parm {int rspsz; int /*<<< orphan*/  addr; int /*<<< orphan*/ * rsp; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int rspsz; int /*<<< orphan*/  addr; int /*<<< orphan*/ * rsp; } ;
struct _adapter {struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _SetAssocSta_CMD_ ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct set_assocsta_parm*,struct set_assocsta_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct set_assocsta_parm*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd (struct cmd_priv*,struct set_assocsta_parm*) ; 

u8 r8712_setassocsta_cmd(struct _adapter *padapter, u8 *mac_addr)
{
	struct cmd_priv			*pcmdpriv = &padapter->cmdpriv;
	struct cmd_obj			*ph2c;
	struct set_assocsta_parm	*psetassocsta_para;
	struct set_assocsta_rsp		*psetassocsta_rsp = NULL;

	ph2c = kmalloc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		return _FAIL;
	psetassocsta_para = kmalloc(sizeof(*psetassocsta_para), GFP_ATOMIC);
	if (!psetassocsta_para) {
		kfree(ph2c);
		return _FAIL;
	}
	psetassocsta_rsp = kmalloc(sizeof(*psetassocsta_rsp), GFP_ATOMIC);
	if (!psetassocsta_rsp) {
		kfree(ph2c);
		kfree(psetassocsta_para);
		return _FAIL;
	}
	init_h2fwcmd_w_parm_no_rsp(ph2c, psetassocsta_para, _SetAssocSta_CMD_);
	ph2c->rsp = (u8 *) psetassocsta_rsp;
	ph2c->rspsz = sizeof(struct set_assocsta_rsp);
	ether_addr_copy(psetassocsta_para->addr, mac_addr);
	r8712_enqueue_cmd(pcmdpriv, ph2c);
	return _SUCCESS;
}