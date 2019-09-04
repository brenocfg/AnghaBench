#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XMLRPC_VALUE_TYPE_EASY ;
typedef  TYPE_2__* XMLRPC_VALUE ;
struct TYPE_5__ {int type; TYPE_1__* v; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlrpc_none ; 
 int /*<<< orphan*/  xmlrpc_type_array ; 
 int /*<<< orphan*/  xmlrpc_type_mixed ; 
 int /*<<< orphan*/  xmlrpc_type_none ; 
 int /*<<< orphan*/  xmlrpc_type_struct ; 
#define  xmlrpc_vector 132 
#define  xmlrpc_vector_array 131 
#define  xmlrpc_vector_mixed 130 
#define  xmlrpc_vector_none 129 
#define  xmlrpc_vector_struct 128 

XMLRPC_VALUE_TYPE_EASY XMLRPC_GetValueTypeEasy (XMLRPC_VALUE value) {
	if (value) {
		switch (value->type) {
		case xmlrpc_vector:
			switch (value->v->type) {
			case xmlrpc_vector_none:
				return xmlrpc_type_none;
			case xmlrpc_vector_struct:
				return xmlrpc_type_struct;
			case xmlrpc_vector_mixed:
				return xmlrpc_type_mixed;
			case xmlrpc_vector_array:
				return xmlrpc_type_array;
			}
		default:
			/* evil cast, but we know they are the same */
			return(XMLRPC_VALUE_TYPE_EASY) value->type;
		}
	}
	return xmlrpc_none;
}