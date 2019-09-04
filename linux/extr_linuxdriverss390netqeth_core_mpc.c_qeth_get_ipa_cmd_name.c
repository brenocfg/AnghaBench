#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum qeth_ipa_cmds { ____Placeholder_qeth_ipa_cmds } qeth_ipa_cmds ;
struct TYPE_3__ {int cmd; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* qeth_ipa_cmd_names ; 

const char *qeth_get_ipa_cmd_name(enum qeth_ipa_cmds cmd)
{
	int x;

	for (x = 0; x < ARRAY_SIZE(qeth_ipa_cmd_names) - 1; x++)
		if (qeth_ipa_cmd_names[x].cmd == cmd)
			return qeth_ipa_cmd_names[x].name;
	return qeth_ipa_cmd_names[x].name;
}