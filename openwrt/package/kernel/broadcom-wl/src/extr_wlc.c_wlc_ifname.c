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
 int GET ; 
 int SET ; 
 char* interface ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int wlc_ifname(wlc_param param, void *data, void *value)
{
	char *val = (char *) value;
	int ret = 0;
	
	if (param & SET) {
		if (strlen(val) < 16)
			strcpy(interface, val);
		else ret = -1;
	}
	if (param & GET) {
		strcpy(val, interface);
	}

	return ret;
}