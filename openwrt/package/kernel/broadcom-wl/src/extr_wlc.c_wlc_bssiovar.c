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
#define  INT 128 
 int PARAM_TYPE ; 
 int SET ; 
 int /*<<< orphan*/  interface ; 
 int /*<<< orphan*/  vif ; 
 int wl_bssiovar_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int) ; 
 int wl_bssiovar_setint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wlc_bssiovar(wlc_param param, void *data, void *value)
{
	int *val = (int *) value;
	char *iov = *((char **) data);
	int ret = 0;
	
	if (param & SET) {
		switch(param & PARAM_TYPE) {
			case INT:
				ret = wl_bssiovar_setint(interface, iov, vif, *val);
		}
	}
	if (param & GET) {
		switch(param & PARAM_TYPE) {
			case INT:
				ret = wl_bssiovar_get(interface, iov, vif, val, sizeof(int));
		}
	}

	return ret;
}