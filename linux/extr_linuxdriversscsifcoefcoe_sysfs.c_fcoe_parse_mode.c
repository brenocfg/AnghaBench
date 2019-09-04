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
typedef  enum fip_conn_type { ____Placeholder_fip_conn_type } fip_conn_type ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int FIP_CONN_TYPE_UNKNOWN ; 
 int /*<<< orphan*/ * fip_conn_type_names ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fip_conn_type fcoe_parse_mode(const char *buf)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(fip_conn_type_names); i++) {
		if (strcasecmp(buf, fip_conn_type_names[i]) == 0)
			return i;
	}

	return FIP_CONN_TYPE_UNKNOWN;
}