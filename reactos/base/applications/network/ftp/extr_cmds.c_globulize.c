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
 int /*<<< orphan*/  blkfree (char**) ; 
 int /*<<< orphan*/  doglob ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** glob (char const*) ; 
 char* globerr ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  stdout ; 

int globulize(const char **cpp)
{
	char **globbed;

	if (!doglob)
		return (1);
	globbed = glob(*cpp);
	if (globerr != NULL) {
		printf("%s: %s\n", *cpp, globerr);
		(void) fflush(stdout);
		if (globbed) {
			blkfree(globbed);
			free((char *)globbed);
		}
		return (0);
	}
	if (globbed) {
		*cpp = *globbed++;
		/* don't waste too much memory */
		if (*globbed) {
			blkfree(globbed);
			free((char *)globbed);
		}
	}
	return (1);
}