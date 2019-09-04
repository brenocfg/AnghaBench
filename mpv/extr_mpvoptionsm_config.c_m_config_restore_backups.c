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
struct m_opt_backup {TYPE_1__* co; int /*<<< orphan*/  backup; struct m_opt_backup* next; } ;
struct m_config {struct m_opt_backup* backup_opts; } ;
struct TYPE_2__ {int is_set_locally; int /*<<< orphan*/  opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_config_set_option_raw (struct m_config*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_option_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct m_opt_backup*) ; 

void m_config_restore_backups(struct m_config *config)
{
    while (config->backup_opts) {
        struct m_opt_backup *bc = config->backup_opts;
        config->backup_opts = bc->next;

        m_config_set_option_raw(config, bc->co, bc->backup, 0);

        m_option_free(bc->co->opt, bc->backup);
        bc->co->is_set_locally = false;
        talloc_free(bc);
    }
}