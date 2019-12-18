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
struct log_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  active_log_contexts ; 
 int /*<<< orphan*/  cached_log_contexts ; 
 int /*<<< orphan*/  da_erase_item (int /*<<< orphan*/ ,struct log_context**) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct log_context**) ; 
 int /*<<< orphan*/  log_contexts_mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_log_context(struct log_context *log_context)
{
	pthread_mutex_lock(&log_contexts_mutex);
	da_erase_item(active_log_contexts, &log_context);
	da_push_back(cached_log_contexts, &log_context);
	pthread_mutex_unlock(&log_contexts_mutex);
}