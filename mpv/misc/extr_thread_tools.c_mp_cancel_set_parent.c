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
struct mp_cancel {int /*<<< orphan*/  lock; struct mp_cancel* parent; int /*<<< orphan*/  slaves; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mp_cancel*) ; 
 int /*<<< orphan*/  LL_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mp_cancel*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retrigger_locked (struct mp_cancel*) ; 
 int /*<<< orphan*/  siblings ; 

void mp_cancel_set_parent(struct mp_cancel *slave, struct mp_cancel *parent)
{
    // We can access c->parent without synchronization, because:
    //  - concurrent mp_cancel_set_parent() calls to slave are not allowed
    //  - slave->parent needs to stay valid as long as the slave exists
    if (slave->parent == parent)
        return;
    if (slave->parent) {
        pthread_mutex_lock(&slave->parent->lock);
        LL_REMOVE(siblings, &slave->parent->slaves, slave);
        pthread_mutex_unlock(&slave->parent->lock);
    }
    slave->parent = parent;
    if (slave->parent) {
        pthread_mutex_lock(&slave->parent->lock);
        LL_APPEND(siblings, &slave->parent->slaves, slave);
        retrigger_locked(slave->parent);
        pthread_mutex_unlock(&slave->parent->lock);
    }
}