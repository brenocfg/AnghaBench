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
struct field_value_data {int dummy; } ;
struct detail_data {int cFields; TYPE_1__* fields; } ;
typedef  int /*<<< orphan*/  create_detailed_value_func ;
struct TYPE_4__ {void* param; int /*<<< orphan*/ * detailed_value; int /*<<< orphan*/  create; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static void add_field_value_data(struct detail_data *data,
 create_detailed_value_func create, void *param)
{
    if (data->cFields)
        data->fields = HeapReAlloc(GetProcessHeap(), 0, data->fields,
         (data->cFields + 1) * sizeof(struct field_value_data));
    else
        data->fields = HeapAlloc(GetProcessHeap(), 0,
         sizeof(struct field_value_data));
    if (data->fields)
    {
        data->fields[data->cFields].create = create;
        data->fields[data->cFields].detailed_value = NULL;
        data->fields[data->cFields].param = param;
        data->cFields++;
    }
}