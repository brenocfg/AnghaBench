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
typedef  int /*<<< orphan*/  va_list ;
struct srcpos {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* srcpos_string (struct srcpos*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void srcpos_verror(struct srcpos *pos, const char *prefix,
		   const char *fmt, va_list va)
{
	char *srcstr;

	srcstr = srcpos_string(pos);

	fprintf(stderr, "%s: %s ", prefix, srcstr);
	vfprintf(stderr, fmt, va);
	fprintf(stderr, "\n");

	free(srcstr);
}