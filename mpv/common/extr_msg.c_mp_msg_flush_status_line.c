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
struct mp_log {scalar_t__ root; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_status_line (scalar_t__) ; 
 int /*<<< orphan*/  mp_msg_lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_msg_flush_status_line(struct mp_log *log)
{
    pthread_mutex_lock(&mp_msg_lock);
    if (log->root)
        flush_status_line(log->root);
    pthread_mutex_unlock(&mp_msg_lock);
}