#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* current; } ;
struct TYPE_4__ {char const* name; } ;
typedef  TYPE_2__ RSpaces ;

/* Variables and functions */

__attribute__((used)) static inline const char *r_spaces_current_name(RSpaces *sp) {
	return sp->current? sp->current->name: "*";
}