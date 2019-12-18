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
struct TYPE_3__ {char const* resultfile; int /*<<< orphan*/  type; int /*<<< orphan*/  test; struct TYPE_3__* next; } ;
typedef  TYPE_1__ _resultmap ;

/* Variables and functions */
 TYPE_1__* resultmap ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static
const char *
get_expectfile(const char *testname, const char *file)
{
	char	   *file_type;
	_resultmap *rm;

	/*
	 * Determine the file type from the file name. This is just what is
	 * following the last dot in the file name.
	 */
	if (!file || !(file_type = strrchr(file, '.')))
		return NULL;

	file_type++;

	for (rm = resultmap; rm != NULL; rm = rm->next)
	{
		if (strcmp(testname, rm->test) == 0 && strcmp(file_type, rm->type) == 0)
		{
			return rm->resultfile;
		}
	}

	return NULL;
}