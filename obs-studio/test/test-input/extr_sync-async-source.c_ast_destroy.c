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
struct async_sync_test {int /*<<< orphan*/  stop_signal; int /*<<< orphan*/  thread; scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct async_sync_test*) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ast_destroy(void *data)
{
	struct async_sync_test *ast = data;

	if (ast->initialized) {
		os_event_signal(ast->stop_signal);
		pthread_join(ast->thread, NULL);
	}

	os_event_destroy(ast->stop_signal);
	bfree(ast);
}