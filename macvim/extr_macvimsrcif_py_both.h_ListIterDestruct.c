#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lw; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ listiterinfo_T ;

/* Variables and functions */
 int /*<<< orphan*/  PyMem_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_rem_watch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ListIterDestruct(listiterinfo_T *lii)
{
    list_rem_watch(lii->list, &lii->lw);
    PyMem_Free(lii);
}