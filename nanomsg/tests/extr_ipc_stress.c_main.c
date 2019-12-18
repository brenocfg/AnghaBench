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
struct nn_thread {int dummy; } ;

/* Variables and functions */
 int THREAD_COUNT ; 
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  server ; 

int main()
{
    int i;
    struct nn_thread srv_thread;
    struct nn_thread cli_threads[THREAD_COUNT];
    /*  Stress the shutdown algorithm. */
    nn_thread_init(&srv_thread, server, NULL);

    for (i = 0; i != THREAD_COUNT; ++i)
        nn_thread_init(&cli_threads[i], client, (void *)(intptr_t)i);
    for (i = 0; i != THREAD_COUNT; ++i)
        nn_thread_term(&cli_threads[i]);

    return 0;
}