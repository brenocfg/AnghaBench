#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
struct TYPE_3__ {int count; int offset; scalar_t__ noCount; } ;
typedef  TYPE_1__ LimitState ;

/* Variables and functions */

__attribute__((used)) static int64
compute_tuples_needed(LimitState *node)
{
	if (node->noCount)
		return -1;
	/* Note: if this overflows, we'll return a negative value, which is OK */
	return node->count + node->offset;
}