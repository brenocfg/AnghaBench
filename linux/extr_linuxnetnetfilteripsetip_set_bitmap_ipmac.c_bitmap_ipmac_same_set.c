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
struct ip_set {scalar_t__ timeout; scalar_t__ extensions; struct bitmap_ipmac* data; } ;
struct bitmap_ipmac {scalar_t__ first_ip; scalar_t__ last_ip; } ;

/* Variables and functions */

__attribute__((used)) static bool
bitmap_ipmac_same_set(const struct ip_set *a, const struct ip_set *b)
{
	const struct bitmap_ipmac *x = a->data;
	const struct bitmap_ipmac *y = b->data;

	return x->first_ip == y->first_ip &&
	       x->last_ip == y->last_ip &&
	       a->timeout == b->timeout &&
	       a->extensions == b->extensions;
}