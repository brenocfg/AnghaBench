#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ispartition; scalar_t__* attislocal; scalar_t__* attisdropped; } ;
typedef  TYPE_1__ TableInfo ;
struct TYPE_6__ {scalar_t__ binary_upgrade; } ;
typedef  TYPE_2__ DumpOptions ;

/* Variables and functions */

bool
shouldPrintColumn(DumpOptions *dopt, TableInfo *tbinfo, int colno)
{
	if (dopt->binary_upgrade)
		return true;
	if (tbinfo->attisdropped[colno])
		return false;
	return (tbinfo->attislocal[colno] || tbinfo->ispartition);
}