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
typedef  int uint64_t ;
struct lwan_thread {int /*<<< orphan*/ * pipe_fd; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  lwan_status_perror (char*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,int*,int) ; 

void lwan_thread_nudge(struct lwan_thread *t)
{
    uint64_t event = 1;

    if (UNLIKELY(write(t->pipe_fd[1], &event, sizeof(event)) < 0))
        lwan_status_perror("write");
}