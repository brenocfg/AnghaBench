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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_path (char const*,char const*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *try_open(const char *dirname, const char *fname, FILE **fp)
{
	char *fullname;

	if (!dirname || fname[0] == '/')
		fullname = xstrdup(fname);
	else
		fullname = join_path(dirname, fname);

	*fp = fopen(fullname, "rb");
	if (!*fp) {
		free(fullname);
		fullname = NULL;
	}

	return fullname;
}