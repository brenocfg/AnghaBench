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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int reorder_size; int /*<<< orphan*/ ** reorder; } ;
typedef  TYPE_1__ MSIWHEREVIEW ;
typedef  int /*<<< orphan*/  MSIROWENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int INITIAL_REORDER_SIZE ; 
 int /*<<< orphan*/  free_reorder (TYPE_1__*) ; 
 int /*<<< orphan*/ ** msi_alloc_zero (int) ; 

__attribute__((used)) static UINT init_reorder(MSIWHEREVIEW *wv)
{
    MSIROWENTRY **new = msi_alloc_zero(sizeof(MSIROWENTRY *) * INITIAL_REORDER_SIZE);
    if (!new)
        return ERROR_OUTOFMEMORY;

    free_reorder(wv);

    wv->reorder = new;
    wv->reorder_size = INITIAL_REORDER_SIZE;

    return ERROR_SUCCESS;
}