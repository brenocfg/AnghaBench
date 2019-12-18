#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VARTYPE ;
struct TYPE_2__ {char const* name; scalar_t__ vt; } ;

/* Variables and functions */
 TYPE_1__* vt_names ; 

__attribute__((used)) static inline const char *vt_to_string(VARTYPE vt)
{
	int i;
	for (i = 0; vt_names[i].name != NULL; i++) {
		if (vt_names[i].vt == vt)
			return vt_names[i].name;
	}
	return "?";
}