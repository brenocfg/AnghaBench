#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ time_str; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__ pdiff ; 
 scalar_t__ strchr (scalar_t__,char) ; 
 char* strdup (scalar_t__) ; 

__attribute__((used)) static int abstime_str_dup(char **pstr)
{
	char *str = NULL;

	if (pdiff.time_str && strchr(pdiff.time_str, ':')) {
		str = strdup(pdiff.time_str);
		if (!str)
			return -ENOMEM;
	}

	*pstr = str;
	return 0;
}