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
typedef  int /*<<< orphan*/  substring_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int kstrtoul (char*,int,unsigned long*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_get_option_ul(substring_t args[], unsigned long *option)
{
	int rc;
	char *string;

	string = match_strdup(args);
	if (string == NULL)
		return -ENOMEM;
	rc = kstrtoul(string, 10, option);
	kfree(string);

	return rc;
}