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
struct setrfintfs_parm {int /*<<< orphan*/  rfintfs; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct _adapter {struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _SetRFIntFs ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct setrfintfs_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 

u8 r8712_setrfintfs_cmd(struct _adapter *padapter, u8 mode)
{
	struct cmd_obj *ph2c;
	struct setrfintfs_parm *psetrfintfsparm;
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;

	ph2c = kmalloc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		return _FAIL;
	psetrfintfsparm = kmalloc(sizeof(*psetrfintfsparm), GFP_ATOMIC);
	if (!psetrfintfsparm) {
		kfree(ph2c);
		return _FAIL;
	}
	init_h2fwcmd_w_parm_no_rsp(ph2c, psetrfintfsparm,
				   GEN_CMD_CODE(_SetRFIntFs));
	psetrfintfsparm->rfintfs = mode;
	r8712_enqueue_cmd(pcmdpriv, ph2c);
	return _SUCCESS;
}