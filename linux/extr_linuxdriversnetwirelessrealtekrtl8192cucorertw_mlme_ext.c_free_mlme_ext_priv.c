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
struct mlme_ext_priv {int /*<<< orphan*/  link_timer; int /*<<< orphan*/  survey_timer; TYPE_1__* padapter; } ;
struct TYPE_2__ {scalar_t__ bDriverStopped; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 

void free_mlme_ext_priv (struct mlme_ext_priv *pmlmeext)
{
	_adapter *padapter = pmlmeext->padapter;

	if (!padapter)
		return;

	if (padapter->bDriverStopped == _TRUE)
	{
		_cancel_timer_ex(&pmlmeext->survey_timer);
		_cancel_timer_ex(&pmlmeext->link_timer);
		//_cancel_timer_ex(&pmlmeext->ADDBA_timer);
	}
}