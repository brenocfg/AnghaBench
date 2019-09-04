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
 int /*<<< orphan*/  ORANGEFS_ALL ; 
 int /*<<< orphan*/  ORANGEFS_VERBOSE ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keyword_is_amalgam(char *keyword)
{
	int rc = 0;

	if ((!strcmp(keyword, ORANGEFS_ALL)) || (!strcmp(keyword, ORANGEFS_VERBOSE)))
		rc = 1;

	return rc;
}