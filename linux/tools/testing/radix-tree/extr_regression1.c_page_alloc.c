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
struct page {int count; int index; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct page* malloc (int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *page_alloc(int index)
{
	struct page *p;
	p = malloc(sizeof(struct page));
	p->count = 1;
	p->index = index;
	pthread_mutex_init(&p->lock, NULL);

	return p;
}