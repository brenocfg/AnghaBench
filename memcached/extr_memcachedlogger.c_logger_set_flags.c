#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  eflags; } ;
typedef  TYPE_1__ logger_watcher ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  eflags; struct TYPE_6__* next; } ;
typedef  TYPE_2__ logger ;

/* Variables and functions */
 int WATCHER_LIMIT ; 
 TYPE_2__* logger_stack_head ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__** watchers ; 

__attribute__((used)) static void logger_set_flags(void) {
    logger *l = NULL;
    int x = 0;
    uint16_t f = 0; /* logger eflags */

    for (x = 0; x < WATCHER_LIMIT; x++) {
        logger_watcher *w = watchers[x];
        if (w == NULL)
            continue;

        f |= w->eflags;
    }
    for (l = logger_stack_head; l != NULL; l=l->next) {
        pthread_mutex_lock(&l->mutex);
        l->eflags = f;
        pthread_mutex_unlock(&l->mutex);
    }
    return;
}