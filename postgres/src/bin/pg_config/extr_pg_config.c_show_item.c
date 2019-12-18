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
struct TYPE_3__ {char* setting; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ConfigData ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_item(const char *configname,
		  ConfigData *configdata,
		  size_t configdata_len)
{
	int			i;

	for (i = 0; i < configdata_len; i++)
	{
		if (strcmp(configname, configdata[i].name) == 0)
			printf("%s\n", configdata[i].setting);
	}
}