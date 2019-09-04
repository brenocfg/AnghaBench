#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mpv_global {TYPE_1__* config; } ;
struct m_config {int dummy; } ;
struct TYPE_2__ {struct m_config* root; } ;

/* Variables and functions */

struct m_config *mp_get_root_config(struct mpv_global *global)
{
    return global->config->root;
}