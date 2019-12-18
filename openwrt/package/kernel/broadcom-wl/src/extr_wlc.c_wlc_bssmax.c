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
typedef  int wlc_param ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE ; 
 int GET ; 
 int /*<<< orphan*/  interface ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 int wl_iovar_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlbuf ; 

__attribute__((used)) static int wlc_bssmax(wlc_param param, void *data, void *value)
{
	int *val = (int *) value;
	char *iov = *((char **) data);
	int ret = -1;

	if (param & GET) {
		ret = wl_iovar_get(interface, iov, wlbuf, BUFSIZE);
		if (!ret) {
			if (strstr(wlbuf, "mbss4"))
				*val = 4;
			else if (strstr(wlbuf, "mbss16"))
				*val = 16;
			else
				*val = 1;
		}
	}

	return ret;
}