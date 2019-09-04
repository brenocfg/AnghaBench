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
struct proc_handler {int /*<<< orphan*/  procs; } ;
typedef  struct proc_handler proc_handler_t ;

/* Variables and functions */
 struct proc_handler* bmalloc (int) ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 

proc_handler_t *proc_handler_create(void)
{
	struct proc_handler *handler = bmalloc(sizeof(struct proc_handler));
	da_init(handler->procs);
	return handler;
}