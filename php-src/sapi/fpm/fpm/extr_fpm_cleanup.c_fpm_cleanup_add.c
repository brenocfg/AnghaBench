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
struct cleanup_s {int type; void (* cleanup ) (int,void*) ;void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanups ; 
 struct cleanup_s* fpm_array_push (int /*<<< orphan*/ *) ; 

int fpm_cleanup_add(int type, void (*cleanup)(int, void *), void *arg) /* {{{ */
{
	struct cleanup_s *c;

	c = fpm_array_push(&cleanups);

	if (!c) {
		return -1;
	}

	c->type = type;
	c->cleanup = cleanup;
	c->arg = arg;

	return 0;
}