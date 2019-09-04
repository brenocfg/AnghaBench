#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int iscsi_switch_str_param(char **param, char *new_val_buf)
{
	char *new_val;

	if (*param) {
		if (!strcmp(*param, new_val_buf))
			return 0;
	}

	new_val = kstrdup(new_val_buf, GFP_NOIO);
	if (!new_val)
		return -ENOMEM;

	kfree(*param);
	*param = new_val;
	return 0;
}