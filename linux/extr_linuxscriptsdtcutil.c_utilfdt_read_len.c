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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int utilfdt_read_err_len (char const*,char**,int /*<<< orphan*/ *) ; 

char *utilfdt_read_len(const char *filename, off_t *len)
{
	char *buff;
	int ret = utilfdt_read_err_len(filename, &buff, len);

	if (ret) {
		fprintf(stderr, "Couldn't open blob from '%s': %s\n", filename,
			strerror(ret));
		return NULL;
	}
	/* Successful read */
	return buff;
}