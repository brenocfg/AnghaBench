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
struct TYPE_2__ {char* value; } ;
typedef  TYPE_1__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_fortune_list_types () ; 

__attribute__((used)) static bool cb_cfg_fortunes_type(void *user, void *data) {
	RConfigNode *node = (RConfigNode *)data;
	if (node->value[0] == '?') {
		r_core_fortune_list_types ();
		return false;
	}
	return true;
}