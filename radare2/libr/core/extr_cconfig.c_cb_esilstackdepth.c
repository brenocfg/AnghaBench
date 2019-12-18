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
struct TYPE_2__ {int i_value; } ;
typedef  TYPE_1__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 

__attribute__((used)) static bool cb_esilstackdepth (void *user, void *data) {
	RConfigNode *node = (RConfigNode*) data;
	if (node->i_value < 3) {
		eprintf ("esil.stack.depth must be greater than 2\n");
		node->i_value = 32;
	}
	return true;
}