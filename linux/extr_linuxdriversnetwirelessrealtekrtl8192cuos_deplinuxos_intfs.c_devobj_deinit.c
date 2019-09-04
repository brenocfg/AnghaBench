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
struct dvobj_priv {int /*<<< orphan*/  setbw_mutex; int /*<<< orphan*/  setch_mutex; int /*<<< orphan*/  h2c_fwcmd_mutex; int /*<<< orphan*/  hw_init_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_mutex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 

void devobj_deinit(struct dvobj_priv *pdvobj)
{
	if(!pdvobj)
		return;

	_rtw_mutex_free(&pdvobj->hw_init_mutex);
	_rtw_mutex_free(&pdvobj->h2c_fwcmd_mutex);
	_rtw_mutex_free(&pdvobj->setch_mutex);
	_rtw_mutex_free(&pdvobj->setbw_mutex);

	rtw_mfree((u8*)pdvobj, sizeof(*pdvobj));
}