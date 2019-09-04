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
struct m_config_option {void* data; } ;
struct m_config {int num_opts; struct m_config_option* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  m_config_notify_change_co (struct m_config*,struct m_config_option*) ; 

void m_config_notify_change_opt_ptr(struct m_config *config, void *ptr)
{
    for (int n = 0; n < config->num_opts; n++) {
        struct m_config_option *co = &config->opts[n];
        if (co->data == ptr) {
            m_config_notify_change_co(config, co);
            return;
        }
    }
    // ptr doesn't point to any config->optstruct field declared in the
    // option list?
    assert(false);
}