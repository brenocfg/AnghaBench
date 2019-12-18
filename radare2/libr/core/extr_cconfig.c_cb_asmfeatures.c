#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* value; } ;
struct TYPE_8__ {TYPE_1__* assembler; } ;
struct TYPE_7__ {int /*<<< orphan*/  features; } ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_node_options (TYPE_3__*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  update_asmfeatures_options (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static bool cb_asmfeatures(void *user, void *data) {
	RCore *core = (RCore *) user;
	RConfigNode *node = (RConfigNode *) data;
	if (*node->value == '?') {
		update_asmfeatures_options (core, node);
		print_node_options (node);
		return 0;
	}
	R_FREE (core->assembler->features);
	if (node->value[0]) {
		core->assembler->features = strdup (node->value);
	}
	return 1;
}