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
typedef  int /*<<< orphan*/  u16 ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  curr_ch; } ;
struct _adapter {TYPE_1__ mppriv; struct cmd_priv cmdpriv; } ;
struct SetChannel_parm {int /*<<< orphan*/  curr_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  _SetChannel ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct SetChannel_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 

void r8712_SetChannel(struct _adapter *pAdapter)
{
	struct cmd_priv *pcmdpriv = &pAdapter->cmdpriv;
	struct cmd_obj *pcmd = NULL;
	struct SetChannel_parm *pparm = NULL;
	u16 code = GEN_CMD_CODE(_SetChannel);

	pcmd = kmalloc(sizeof(*pcmd), GFP_ATOMIC);
	if (!pcmd)
		return;
	pparm = kmalloc(sizeof(*pparm), GFP_ATOMIC);
	if (!pparm) {
		kfree(pcmd);
		return;
	}
	pparm->curr_ch = pAdapter->mppriv.curr_ch;
	init_h2fwcmd_w_parm_no_rsp(pcmd, pparm, code);
	r8712_enqueue_cmd(pcmdpriv, pcmd);
}