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
struct TYPE_3__ {scalar_t__ using_immediate; } ;
typedef  TYPE_1__ graphics_t ;

/* Variables and functions */
 size_t IMMEDIATE_COUNT ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,size_t) ; 

__attribute__((used)) static inline bool validvertsize(graphics_t *graphics, size_t num,
				 const char *name)
{
	if (graphics->using_immediate && num == IMMEDIATE_COUNT) {
		blog(LOG_ERROR,
		     "%s: tried to use over %u "
		     "for immediate rendering",
		     name, IMMEDIATE_COUNT);
		return false;
	}

	return true;
}