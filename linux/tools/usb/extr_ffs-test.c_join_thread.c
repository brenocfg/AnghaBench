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
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void join_thread(struct thread *t)
{
	int ret = pthread_join(t->id, NULL);

	if (ret < 0)
		err("%s: joining thread", t->filename);
	else
		debug("%s: joined\n", t->filename);
}