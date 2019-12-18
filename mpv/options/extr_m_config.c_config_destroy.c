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
struct m_config {TYPE_1__* shadow; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ num_listeners; int /*<<< orphan*/  lock; struct TYPE_2__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  m_config_restore_backups (struct m_config*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 

__attribute__((used)) static void config_destroy(void *p)
{
    struct m_config *config = p;
    m_config_restore_backups(config);

    talloc_free(config->data);

    if (config->shadow) {
        // must all have been unregistered
        assert(config->shadow->num_listeners == 0);
        talloc_free(config->shadow->data);
        pthread_mutex_destroy(&config->shadow->lock);
        talloc_free(config->shadow);
    }
}