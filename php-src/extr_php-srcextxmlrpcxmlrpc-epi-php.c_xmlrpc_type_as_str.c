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
typedef  size_t XMLRPC_VECTOR_TYPE ;
typedef  size_t XMLRPC_VALUE_TYPE ;

/* Variables and functions */
 size_t XMLRPC_TYPE_COUNT ; 
 char** get_type_str_mapping () ; 
 size_t xmlrpc_vector_none ; 

const char* xmlrpc_type_as_str(XMLRPC_VALUE_TYPE type, XMLRPC_VECTOR_TYPE vtype) /* {{{ */
{
	const char** str_mapping = get_type_str_mapping();

	if (vtype == xmlrpc_vector_none) {
		return str_mapping[type];
	} else {
		return str_mapping[XMLRPC_TYPE_COUNT + vtype];
	}
}