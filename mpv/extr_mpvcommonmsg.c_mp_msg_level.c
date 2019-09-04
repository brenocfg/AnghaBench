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
struct mp_log_root {int /*<<< orphan*/  reload_counter; } ;
struct mp_log {int level; int /*<<< orphan*/  reload_counter; struct mp_log_root* root; } ;

/* Variables and functions */
 scalar_t__ atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  update_loglevel (struct mp_log*) ; 

int mp_msg_level(struct mp_log *log)
{
    struct mp_log_root *root = log->root;
    if (!root)
        return -1;
    if (atomic_load_explicit(&log->reload_counter, memory_order_relaxed) !=
        atomic_load_explicit(&root->reload_counter, memory_order_relaxed))
    {
        update_loglevel(log);
    }
    return log->level;
}