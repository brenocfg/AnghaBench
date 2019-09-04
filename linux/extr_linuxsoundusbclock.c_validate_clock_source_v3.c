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
struct uac3_clock_source_descriptor {int bLength; int bClockID; } ;

/* Variables and functions */

__attribute__((used)) static bool validate_clock_source_v3(void *p, int id)
{
	struct uac3_clock_source_descriptor *cs = p;
	return cs->bLength == sizeof(*cs) && cs->bClockID == id;
}