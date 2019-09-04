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
struct seg6_local_lwt {scalar_t__ iif; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_nla_iif(struct seg6_local_lwt *a, struct seg6_local_lwt *b)
{
	if (a->iif != b->iif)
		return 1;

	return 0;
}