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
struct evt_priv {void* c2h_queue; scalar_t__ c2h_wk_alive; int /*<<< orphan*/  c2h_wk; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _cancel_workitem_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtw_cbuf_empty (void*) ; 
 void* rtw_cbuf_pop (void*) ; 

void _rtw_free_evt_priv(struct	evt_priv *pevtpriv)
{
	RT_TRACE(_module_rtl871x_cmd_c_, _drv_info_, ("+_rtw_free_evt_priv\n"));

	_cancel_workitem_sync(&pevtpriv->c2h_wk);
	while (pevtpriv->c2h_wk_alive)
		msleep(10);

	while (!rtw_cbuf_empty(pevtpriv->c2h_queue)) {
		void *c2h = rtw_cbuf_pop(pevtpriv->c2h_queue);
		if (c2h != NULL && c2h != (void *)pevtpriv) {
			kfree(c2h);
		}
	}
	kfree(pevtpriv->c2h_queue);

	RT_TRACE(_module_rtl871x_cmd_c_, _drv_info_, ("-_rtw_free_evt_priv\n"));
}