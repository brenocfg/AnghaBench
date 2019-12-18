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
 int /*<<< orphan*/  PG_MAJORVERSION ; 
 int /*<<< orphan*/  PG_VERSION ; 
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  process_file (char*,int) ; 
 char* psprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_psqlrc_file(char *filename)
{
	char	   *psqlrc_minor,
			   *psqlrc_major;

#if defined(WIN32) && (!defined(__MINGW32__))
#define R_OK 4
#endif

	psqlrc_minor = psprintf("%s-%s", filename, PG_VERSION);
	psqlrc_major = psprintf("%s-%s", filename, PG_MAJORVERSION);

	/* check for minor version first, then major, then no version */
	if (access(psqlrc_minor, R_OK) == 0)
		(void) process_file(psqlrc_minor, false);
	else if (access(psqlrc_major, R_OK) == 0)
		(void) process_file(psqlrc_major, false);
	else if (access(filename, R_OK) == 0)
		(void) process_file(filename, false);

	free(psqlrc_minor);
	free(psqlrc_major);
}