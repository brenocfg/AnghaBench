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
 scalar_t__ workshop_get_positions (int /*<<< orphan*/ *,char**,int*,int*,int*,int*,int*,int*,int*,char**) ; 

char *
workshop_test_getselectedtext()
{
    char	*filename, *selection;
    int		curLine, curCol, selStartLine, selStartCol, selEndLine;
    int		selEndCol, selLength;

    if (workshop_get_positions(
		NULL, &filename, &curLine, &curCol, &selStartLine,
		&selStartCol, &selEndLine, &selEndCol, &selLength,
		&selection))
	return selection;
    else
	return NULL;
}