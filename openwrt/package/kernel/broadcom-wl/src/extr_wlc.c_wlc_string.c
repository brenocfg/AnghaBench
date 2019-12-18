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
 int PARAM_MODE ; 
 int /*<<< orphan*/  strcpy (void*,char*) ; 

__attribute__((used)) static int wlc_string(wlc_param param, void *data, void *value)
{
	char *var = *((char **) data);
	
	if ((param & PARAM_MODE) == GET) {
		strcpy(value, var);
	}

	return 0;
}