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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OCFS2_FILECHECK_ERR_END ; 
 int OCFS2_FILECHECK_ERR_START ; 
 char const** ocfs2_filecheck_errs ; 

__attribute__((used)) static const char *
ocfs2_filecheck_error(int errno)
{
	if (!errno)
		return ocfs2_filecheck_errs[errno];

	BUG_ON(errno < OCFS2_FILECHECK_ERR_START ||
	       errno > OCFS2_FILECHECK_ERR_END);
	return ocfs2_filecheck_errs[errno - OCFS2_FILECHECK_ERR_START + 1];
}