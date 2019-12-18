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
struct TYPE_2__ {scalar_t__ value; } ;
typedef  TYPE_1__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  R_SYS_HOME ; 
 int /*<<< orphan*/  r_sys_setenv (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool cb_dirhome(void *user, void *data) {
	RConfigNode *node = (RConfigNode*) data;
	if (node->value) {
		r_sys_setenv (R_SYS_HOME, node->value);
	}
	return true;
}