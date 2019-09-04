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
typedef  int /*<<< orphan*/  u32 ;
struct cmd_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_init_cmd_priv (struct cmd_priv*) ; 

u32	rtw_init_cmd_priv(struct cmd_priv *pcmdpriv)
{
	u32	res;
_func_enter_;	
	res = _rtw_init_cmd_priv (pcmdpriv);
_func_exit_;	
	return res;	
}