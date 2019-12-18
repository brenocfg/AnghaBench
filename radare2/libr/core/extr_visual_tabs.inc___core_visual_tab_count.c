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
struct TYPE_4__ {scalar_t__ tabs; } ;
struct TYPE_5__ {TYPE_1__ visual; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int r_list_length (scalar_t__) ; 

__attribute__((used)) static int __core_visual_tab_count (RCore *core) {
	return core->visual.tabs? r_list_length (core->visual.tabs): 0;
}