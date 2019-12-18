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
struct pool {void* mem; struct pool* next; } ;

/* Variables and functions */
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (struct pool*) ; 
 struct pool* pool_head ; 

__attribute__((used)) static void *my_malloc(size_t size)
{
	struct pool *p;

	p = calloc(1, sizeof(struct pool));
	if (!p)
		return NULL;

	p->mem = calloc(1, size);
	if (!p->mem) {
		free(p);
		return NULL;
	}

	p->next = pool_head;
	pool_head = p;

	return p->mem;
}