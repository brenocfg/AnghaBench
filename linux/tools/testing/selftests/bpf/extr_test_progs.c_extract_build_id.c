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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 

int extract_build_id(char *build_id, size_t size)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;

	fp = popen("readelf -n ./urandom_read | grep 'Build ID'", "r");
	if (fp == NULL)
		return -1;

	if (getline(&line, &len, fp) == -1)
		goto err;
	fclose(fp);

	if (len > size)
		len = size;
	memcpy(build_id, line, len);
	build_id[len] = '\0';
	return 0;
err:
	fclose(fp);
	return -1;
}