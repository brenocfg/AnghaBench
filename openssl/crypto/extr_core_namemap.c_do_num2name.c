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
struct num2name_data_st {scalar_t__ idx; char const* name; } ;

/* Variables and functions */

__attribute__((used)) static void do_num2name(const char *name, void *vdata)
{
    struct num2name_data_st *data = vdata;

    if (data->idx > 0)
        data->idx--;
    else if (data->name == NULL)
        data->name = name;
}