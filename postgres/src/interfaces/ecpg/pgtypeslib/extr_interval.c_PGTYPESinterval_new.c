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
typedef  int /*<<< orphan*/  interval ;

/* Variables and functions */
 scalar_t__ pgtypes_alloc (int) ; 

interval *
PGTYPESinterval_new(void)
{
	interval   *result;

	result = (interval *) pgtypes_alloc(sizeof(interval));
	/* result can be NULL if we run out of memory */
	return result;
}