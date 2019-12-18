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
struct event_node {int event_time; } ;
typedef  int s64 ;

/* Variables and functions */

__attribute__((used)) static int compar(const void *a, const void *b)
{
	const struct event_node *nodea = a;
	const struct event_node *nodeb = b;
	s64 cmp = nodea->event_time - nodeb->event_time;

	return cmp;
}