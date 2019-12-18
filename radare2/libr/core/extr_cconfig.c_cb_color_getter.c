#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {TYPE_1__* context; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; int /*<<< orphan*/  i_value; } ;
struct TYPE_6__ {int /*<<< orphan*/  color_mode; } ;
typedef  TYPE_2__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_config_node_value_format_i (char*,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_3__* r_cons_singleton () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static bool cb_color_getter(void *user, RConfigNode *node) {
	(void)user;
	node->i_value = r_cons_singleton ()->context->color_mode;
	char buf[128];
	r_config_node_value_format_i (buf, sizeof (buf), r_cons_singleton ()->context->color_mode, node);
	if (!node->value || strcmp (node->value, buf) != 0) {
		free (node->value);
		node->value = strdup (buf);
	}
	return true;
}