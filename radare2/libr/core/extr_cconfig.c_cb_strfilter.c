#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* value; } ;
struct TYPE_6__ {TYPE_1__* bin; } ;
struct TYPE_5__ {char strfilter; } ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  print_node_options (TYPE_3__*) ; 
 int /*<<< orphan*/  r_cons_printf (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool cb_strfilter(void *user, void *data) {
	RCore *core = (RCore*) user;
	RConfigNode *node = (RConfigNode*) data;
	if (node->value[0] == '?') {
		if (strlen (node->value) > 1 && node->value[1] == '?') {
			r_cons_printf ("Valid values for bin.str.filter:\n"
				"a  only alphanumeric printable\n"
				"8  only strings with utf8 chars\n"
				"p  file/directory paths\n"
				"e  email-like addresses\n"
				"u  urls\n"
				"i  IPv4 address-like strings\n"
				"U  only uppercase strings\n"
				"f  format-strings\n");
		} else {
			print_node_options (node);
		}
		return false;
	} else {
		core->bin->strfilter = node->value[0];
	}
	return true;
}