#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buildCxt; } ;
typedef  TYPE_1__ IspellDict ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurTransactionContext ; 

void
NIStartBuild(IspellDict *Conf)
{
	/*
	 * The temp context is a child of CurTransactionContext, so that it will
	 * go away automatically on error.
	 */
	Conf->buildCxt = AllocSetContextCreate(CurTransactionContext,
										   "Ispell dictionary init context",
										   ALLOCSET_DEFAULT_SIZES);
}