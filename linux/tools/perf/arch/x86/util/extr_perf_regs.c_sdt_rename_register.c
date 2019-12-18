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
struct TYPE_2__ {int /*<<< orphan*/  uprobe_name; int /*<<< orphan*/ * sdt_name; } ;

/* Variables and functions */
 TYPE_1__* sdt_reg_tbl ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void sdt_rename_register(char *sdt_reg, int sdt_len, char *uprobe_reg)
{
	int i = 0;

	for (i = 0; sdt_reg_tbl[i].sdt_name != NULL; i++) {
		if (!strncmp(sdt_reg_tbl[i].sdt_name, sdt_reg, sdt_len)) {
			strcpy(uprobe_reg, sdt_reg_tbl[i].uprobe_name);
			return;
		}
	}

	strncpy(uprobe_reg, sdt_reg, sdt_len);
}