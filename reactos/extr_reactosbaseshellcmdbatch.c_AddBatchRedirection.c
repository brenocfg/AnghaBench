#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {TYPE_1__* RedirList; } ;
struct TYPE_4__ {struct TYPE_4__* Next; } ;
typedef  TYPE_1__ REDIRECTION ;

/* Variables and functions */
 TYPE_2__* bc ; 

VOID AddBatchRedirection(REDIRECTION **RedirList)
{
    REDIRECTION **ListEnd;

    /* Prepend the list to the batch context's list */
    ListEnd = RedirList;
    while (*ListEnd)
        ListEnd = &(*ListEnd)->Next;
    *ListEnd = bc->RedirList;
    bc->RedirList = *RedirList;

    /* Null out the pointer so that the list will not be cleared prematurely.
     * These redirections should persist until the batch file exits. */
    *RedirList = NULL;
}