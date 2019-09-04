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
struct setbasicrate_parm {int /*<<< orphan*/  basicrates; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct _adapter {struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NumRates ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _SetBasicRate_CMD_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct setbasicrate_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 

u8 r8712_setbasicrate_cmd(struct _adapter *padapter, u8 *rateset)
{
	struct cmd_obj *ph2c;
	struct setbasicrate_parm *pssetbasicratepara;
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;

	ph2c = kmalloc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		return _FAIL;
	pssetbasicratepara = kmalloc(sizeof(*pssetbasicratepara), GFP_ATOMIC);
	if (!pssetbasicratepara) {
		kfree(ph2c);
		return _FAIL;
	}
	init_h2fwcmd_w_parm_no_rsp(ph2c, pssetbasicratepara,
		_SetBasicRate_CMD_);
	memcpy(pssetbasicratepara->basicrates, rateset, NumRates);
	r8712_enqueue_cmd(pcmdpriv, ph2c);
	return _SUCCESS;
}