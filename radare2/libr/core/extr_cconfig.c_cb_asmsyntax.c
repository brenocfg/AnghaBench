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
struct TYPE_5__ {char* value; } ;
struct TYPE_4__ {int /*<<< orphan*/  assembler; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  print_node_options (TYPE_2__*) ; 
 int /*<<< orphan*/  r_asm_set_syntax (int /*<<< orphan*/ ,int) ; 
 int r_asm_syntax_from_string (char*) ; 

__attribute__((used)) static bool cb_asmsyntax(void *user, void *data) {
	RCore *core = (RCore*) user;
	RConfigNode *node = (RConfigNode*) data;
	if (*node->value == '?') {
		print_node_options (node);
		return false;
	} else {
		int syntax = r_asm_syntax_from_string (node->value);
		if (syntax == -1) {
			return false;
		}
		r_asm_set_syntax (core->assembler, syntax);
	}
	return true;
}