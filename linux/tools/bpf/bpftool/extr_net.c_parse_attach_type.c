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
typedef  enum net_attach_type { ____Placeholder_net_attach_type } net_attach_type ;

/* Variables and functions */
 scalar_t__* attach_type_strings ; 
 scalar_t__ is_prefix (char const*,scalar_t__) ; 
 int net_attach_type_size ; 

__attribute__((used)) static enum net_attach_type parse_attach_type(const char *str)
{
	enum net_attach_type type;

	for (type = 0; type < net_attach_type_size; type++) {
		if (attach_type_strings[type] &&
		    is_prefix(str, attach_type_strings[type]))
			return type;
	}

	return net_attach_type_size;
}