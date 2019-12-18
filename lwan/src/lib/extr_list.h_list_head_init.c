#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct TYPE_2__* prev; struct TYPE_2__* next; } ;
struct list_head {TYPE_1__ n; } ;

/* Variables and functions */

__attribute__((used)) static inline void list_head_init(struct list_head *h)
{
	h->n.next = h->n.prev = &h->n;
}