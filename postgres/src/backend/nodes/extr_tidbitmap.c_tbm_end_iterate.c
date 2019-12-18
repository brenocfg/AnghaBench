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
typedef  int /*<<< orphan*/  TBMIterator ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

void
tbm_end_iterate(TBMIterator *iterator)
{
	pfree(iterator);
}