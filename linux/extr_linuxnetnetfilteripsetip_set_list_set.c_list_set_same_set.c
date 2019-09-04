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
struct list_set {scalar_t__ size; } ;
struct ip_set {scalar_t__ timeout; scalar_t__ extensions; struct list_set* data; } ;

/* Variables and functions */

__attribute__((used)) static bool
list_set_same_set(const struct ip_set *a, const struct ip_set *b)
{
	const struct list_set *x = a->data;
	const struct list_set *y = b->data;

	return x->size == y->size &&
	       a->timeout == b->timeout &&
	       a->extensions == b->extensions;
}