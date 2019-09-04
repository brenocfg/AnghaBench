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
struct m_config_option {int dummy; } ;
struct m_config {struct m_config_option* opts; } ;

/* Variables and functions */

struct m_config_option *m_config_get_co_index(struct m_config *config, int index)
{
    return &config->opts[index];
}