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
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMMSTR_NO_CLOSE ; 
 char* kstrndup (char*,size_t,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  trace_probe_log_err (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __parse_imm_string(char *str, char **pbuf, int offs)
{
	size_t len = strlen(str);

	if (str[len - 1] != '"') {
		trace_probe_log_err(offs + len, IMMSTR_NO_CLOSE);
		return -EINVAL;
	}
	*pbuf = kstrndup(str, len - 1, GFP_KERNEL);
	return 0;
}