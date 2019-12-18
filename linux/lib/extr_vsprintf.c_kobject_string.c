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
struct printf_spec {int dummy; } ;

/* Variables and functions */
 char* device_node_string (char*,char*,void*,struct printf_spec,char const*) ; 
 char* error_string (char*,char*,char*,struct printf_spec) ; 

__attribute__((used)) static char *kobject_string(char *buf, char *end, void *ptr,
			    struct printf_spec spec, const char *fmt)
{
	switch (fmt[1]) {
	case 'F':
		return device_node_string(buf, end, ptr, spec, fmt + 1);
	}

	return error_string(buf, end, "(%pO?)", spec);
}