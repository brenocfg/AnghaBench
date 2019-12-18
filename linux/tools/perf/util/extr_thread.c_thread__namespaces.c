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
struct thread {int /*<<< orphan*/  namespaces_lock; } ;
struct namespaces {int dummy; } ;

/* Variables and functions */
 struct namespaces* __thread__namespaces (struct thread*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct namespaces *thread__namespaces(struct thread *thread)
{
	struct namespaces *ns;

	down_read(&thread->namespaces_lock);
	ns = __thread__namespaces(thread);
	up_read(&thread->namespaces_lock);

	return ns;
}