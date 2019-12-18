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
struct m_group_data {int dummy; } ;
struct m_config_data {int group_index; int num_gdata; struct m_group_data* gdata; } ;

/* Variables and functions */

__attribute__((used)) static struct m_group_data *m_config_gdata(struct m_config_data *data,
                                           int group_index)
{
    if (group_index < data->group_index ||
        group_index >= data->group_index + data->num_gdata)
        return NULL;

    return &data->gdata[group_index - data->group_index];
}