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
struct TYPE_4__ {int /*<<< orphan*/  data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ list_item_t ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  NO_ERROR ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static DWORD
AddListItem(list_item_t **pfirst, LPVOID data)
{
    list_item_t *new_item = malloc(sizeof(list_item_t));
    if (new_item == NULL)
    {
        return ERROR_OUTOFMEMORY;
    }

    new_item->next = *pfirst;
    new_item->data = data;

    *pfirst = new_item;
    return NO_ERROR;
}