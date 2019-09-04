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
struct event_format {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static int events_id_cmp(const void *a, const void *b)
{
	struct event_format * const * ea = a;
	struct event_format * const * eb = b;

	if ((*ea)->id < (*eb)->id)
		return -1;

	if ((*ea)->id > (*eb)->id)
		return 1;

	return 0;
}