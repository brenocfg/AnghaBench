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
typedef  enum sof_ipc_process_type { ____Placeholder_sof_ipc_process_type } sof_ipc_process_type ;
struct TYPE_3__ {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int SOF_PROCESS_NONE ; 
 TYPE_1__* sof_process ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sof_ipc_process_type find_process(const char *name)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(sof_process); i++) {
		if (strcmp(name, sof_process[i].name) == 0)
			return sof_process[i].type;
	}

	return SOF_PROCESS_NONE;
}