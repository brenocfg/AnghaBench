#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ShortData; } ;
struct TYPE_5__ {scalar_t__ shortData; } ;
struct TYPE_7__ {int bValid; TYPE_2__ BaStartSeqCtrl; scalar_t__ DialogToken; scalar_t__ BaTimeoutValue; TYPE_1__ BaParamSet; } ;
typedef  TYPE_3__* PBA_RECORD ;

/* Variables and functions */

void ResetBaEntry(PBA_RECORD pBA)
{
	pBA->bValid			= false;
	pBA->BaParamSet.shortData	= 0;
	pBA->BaTimeoutValue		= 0;
	pBA->DialogToken		= 0;
	pBA->BaStartSeqCtrl.ShortData	= 0;
}