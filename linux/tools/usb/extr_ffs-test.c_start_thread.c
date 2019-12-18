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
struct thread {int /*<<< orphan*/  filename; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_on (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  start_thread_helper ; 

__attribute__((used)) static void start_thread(struct thread *t)
{
	debug("%s: starting\n", t->filename);

	die_on(pthread_create(&t->id, NULL, start_thread_helper, t) < 0,
	       "pthread_create(%s)", t->filename);
}