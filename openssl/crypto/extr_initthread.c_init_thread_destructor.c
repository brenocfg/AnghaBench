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
typedef  int /*<<< orphan*/  THREAD_EVENT_HANDLER ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (void*) ; 
 int /*<<< orphan*/  init_thread_remove_handlers (void*) ; 
 int /*<<< orphan*/  init_thread_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void init_thread_destructor(void *hands)
{
    init_thread_stop(NULL, (THREAD_EVENT_HANDLER **)hands);
    init_thread_remove_handlers(hands);
    OPENSSL_free(hands);
}