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
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DEBUG_LVL2 ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int snprintf (char*,size_t,char*,char*,char*) ; 
 int system (char*) ; 

int create_zip_file(char *zip_filename, char *bin_filename) {
	int exitcode = 0;

	char *buffer;
	size_t buffer_size;
	int count;

	buffer_size = 1000;
	buffer = NULL;
	do {
		// allocate memory for command line
		if (!buffer) {
			buffer = malloc(buffer_size);
		}
		if (!buffer) {
			exitcode = 1;
			printf("create_zip_file: can not allocate %i bytes\n", (int) buffer_size);
			break;
		}

		// if buffer was not completely filled, then line fit in completely
		count = snprintf(buffer, buffer_size, "zip \"%s\" \"%s\"", zip_filename, bin_filename);
		if ((count > -1) && (count < buffer_size)) {
			break;
		}

		// otherwise try again with more space
		if (count > -1) {	// glibc 2.1
			buffer_size = count + 1;	// precisely what is needed
		} else {	// glibc 2.0
			buffer_size *= 2;	// twice the old size
		}
		free(buffer);
		buffer = NULL;
		lprintf(DEBUG_LVL2, " extending buffer to %i bytes\n", buffer_size);
	} while (1);

	if (!exitcode) {
		// zipping binfile
		lprintf(DEBUG, "%s\n", buffer);
		count = system(buffer);
		if ((count < 0) || (WEXITSTATUS(count))) {
			exitcode = 1;
			printf("create_zip_file: can not execute %s bytes\n", buffer);
		}
	}

	return exitcode;
}