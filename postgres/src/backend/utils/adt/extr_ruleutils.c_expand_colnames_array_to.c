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
struct TYPE_3__ {int num_cols; char** colnames; } ;
typedef  TYPE_1__ deparse_columns ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc0 (int) ; 
 scalar_t__ repalloc (char**,int) ; 

__attribute__((used)) static void
expand_colnames_array_to(deparse_columns *colinfo, int n)
{
	if (n > colinfo->num_cols)
	{
		if (colinfo->colnames == NULL)
			colinfo->colnames = (char **) palloc0(n * sizeof(char *));
		else
		{
			colinfo->colnames = (char **) repalloc(colinfo->colnames,
												   n * sizeof(char *));
			memset(colinfo->colnames + colinfo->num_cols, 0,
				   (n - colinfo->num_cols) * sizeof(char *));
		}
		colinfo->num_cols = n;
	}
}