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
struct _ioeventfd {int /*<<< orphan*/  list; int /*<<< orphan*/  eventfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  eventfd_ctx_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct _ioeventfd*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ioeventfd_release(struct _ioeventfd *p)
{
	eventfd_ctx_put(p->eventfd);
	list_del(&p->list);
	kfree(p);
}