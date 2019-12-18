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
struct playlist_param {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  m_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_SETOPT_BACKUP ; 
 int /*<<< orphan*/  m_config_set_option_cli (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_per_file_options(m_config_t *conf,
                                  struct playlist_param *params,
                                  int params_count)
{
    for (int n = 0; n < params_count; n++) {
        m_config_set_option_cli(conf, params[n].name, params[n].value,
                                M_SETOPT_BACKUP);
    }
}