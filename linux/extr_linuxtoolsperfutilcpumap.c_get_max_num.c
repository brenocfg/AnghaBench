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
 scalar_t__ filename__read_str (char*,char**,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int sscanf (char*,char*,int*) ; 

__attribute__((used)) static int get_max_num(char *path, int *max)
{
	size_t num;
	char *buf;
	int err = 0;

	if (filename__read_str(path, &buf, &num))
		return -1;

	buf[num] = '\0';

	/* start on the right, to find highest node num */
	while (--num) {
		if ((buf[num] == ',') || (buf[num] == '-')) {
			num++;
			break;
		}
	}
	if (sscanf(&buf[num], "%d", max) < 1) {
		err = -1;
		goto out;
	}

	/* convert from 0-based to 1-based */
	(*max)++;

out:
	free(buf);
	return err;
}