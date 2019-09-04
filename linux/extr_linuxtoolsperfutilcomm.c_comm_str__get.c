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
struct comm_str {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct comm_str *comm_str__get(struct comm_str *cs)
{
	if (cs && refcount_inc_not_zero(&cs->refcnt))
		return cs;

	return NULL;
}