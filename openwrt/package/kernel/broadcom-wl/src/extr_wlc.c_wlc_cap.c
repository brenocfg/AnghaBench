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
 int wl_iovar_get (int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wlc_cap(wlc_param param, void *data, void *value)
{
	char *iov = *((char **) data);

	if (param & GET)
		return wl_iovar_get(interface, iov, value, BUFSIZE);

	return -1;
}