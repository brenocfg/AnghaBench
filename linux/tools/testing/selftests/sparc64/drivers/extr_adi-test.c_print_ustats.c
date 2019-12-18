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
struct stats {scalar_t__ count; scalar_t__ bytes; scalar_t__ total; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT_L1 (char*,int /*<<< orphan*/ ,scalar_t__,float,float) ; 

__attribute__((used)) static void print_ustats(const struct stats * const ustats)
{
	DEBUG_PRINT_L1("%s\t%7d\t%7.0f\t%7.0f\n",
		       ustats->name, ustats->count,
		       (float)ustats->total / (float)ustats->count,
		       (float)ustats->bytes / (float)ustats->count);
}