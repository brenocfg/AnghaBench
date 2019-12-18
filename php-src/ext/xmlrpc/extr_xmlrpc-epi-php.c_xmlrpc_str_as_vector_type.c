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
typedef  int /*<<< orphan*/  XMLRPC_VECTOR_TYPE ;

/* Variables and functions */
 int TYPE_STR_MAP_SIZE ; 
 int XMLRPC_TYPE_COUNT ; 
 char** get_type_str_mapping () ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  xmlrpc_vector_none ; 

XMLRPC_VECTOR_TYPE xmlrpc_str_as_vector_type(const char* str) /* {{{ */
{
	const char** str_mapping = get_type_str_mapping();
	int i;

	if (str) {
		for (i = XMLRPC_TYPE_COUNT; i < TYPE_STR_MAP_SIZE; i++) {
			if (!strcmp(str_mapping[i], str)) {
				return (XMLRPC_VECTOR_TYPE) (i - XMLRPC_TYPE_COUNT);
			}
		}
	}
	return xmlrpc_vector_none;
}