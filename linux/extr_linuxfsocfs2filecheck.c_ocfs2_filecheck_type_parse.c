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
 unsigned int OCFS2_FILECHECK_TYPE_CHK ; 
 unsigned int OCFS2_FILECHECK_TYPE_FIX ; 
 unsigned int OCFS2_FILECHECK_TYPE_SET ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
ocfs2_filecheck_type_parse(const char *name, unsigned int *type)
{
	if (!strncmp(name, "fix", 4))
		*type = OCFS2_FILECHECK_TYPE_FIX;
	else if (!strncmp(name, "check", 6))
		*type = OCFS2_FILECHECK_TYPE_CHK;
	else if (!strncmp(name, "set", 4))
		*type = OCFS2_FILECHECK_TYPE_SET;
	else
		return 1;

	return 0;
}