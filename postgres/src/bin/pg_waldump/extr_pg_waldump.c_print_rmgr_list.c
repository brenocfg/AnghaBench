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
struct TYPE_2__ {char* rm_name; } ;

/* Variables and functions */
 int RM_MAX_ID ; 
 TYPE_1__* RmgrDescTable ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
print_rmgr_list(void)
{
	int			i;

	for (i = 0; i <= RM_MAX_ID; i++)
	{
		printf("%s\n", RmgrDescTable[i].rm_name);
	}
}