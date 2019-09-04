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
struct ccw_dev_id {unsigned int ssid; unsigned int devno; } ;

/* Variables and functions */
 int CCW_BUS_ID_SIZE ; 
 int EINVAL ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*,unsigned int*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int __get_next_id(const char **buf, struct ccw_dev_id *id)
{
	unsigned int cssid, ssid, devno;
	int ret = 0, len;
	char *start, *end;

	start = (char *)*buf;
	end = strchr(start, ',');
	if (!end) {
		/* Last entry. Strip trailing newline, if applicable. */
		end = strchr(start, '\n');
		if (end)
			*end = '\0';
		len = strlen(start) + 1;
	} else {
		len = end - start + 1;
		end++;
	}
	if (len <= CCW_BUS_ID_SIZE) {
		if (sscanf(start, "%2x.%1x.%04x", &cssid, &ssid, &devno) != 3)
			ret = -EINVAL;
	} else
		ret = -EINVAL;

	if (!ret) {
		id->ssid = ssid;
		id->devno = devno;
	}
	*buf = end;
	return ret;
}