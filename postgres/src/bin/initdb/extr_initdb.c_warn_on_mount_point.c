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
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
warn_on_mount_point(int error)
{
	if (error == 2)
		fprintf(stderr,
				_("It contains a dot-prefixed/invisible file, perhaps due to it being a mount point.\n"));
	else if (error == 3)
		fprintf(stderr,
				_("It contains a lost+found directory, perhaps due to it being a mount point.\n"));

	fprintf(stderr,
			_("Using a mount point directly as the data directory is not recommended.\n"
			  "Create a subdirectory under the mount point.\n"));
}