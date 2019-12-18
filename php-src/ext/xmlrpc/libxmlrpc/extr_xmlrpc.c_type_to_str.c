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
typedef  int XMLRPC_VALUE_TYPE ;

/* Variables and functions */
#define  xmlrpc_base64 140 
#define  xmlrpc_boolean 139 
#define  xmlrpc_datetime 138 
#define  xmlrpc_double 137 
#define  xmlrpc_empty 136 
#define  xmlrpc_int 135 
#define  xmlrpc_none 134 
#define  xmlrpc_string 133 
#define  xmlrpc_vector 132 
#define  xmlrpc_vector_array 131 
#define  xmlrpc_vector_mixed 130 
#define  xmlrpc_vector_none 129 
#define  xmlrpc_vector_struct 128 

const char* type_to_str(XMLRPC_VALUE_TYPE type, XMLRPC_VECTOR_TYPE vtype) {
    switch(type) {
       case xmlrpc_none:
          return "none";
       case xmlrpc_empty:
          return "empty";
       case xmlrpc_base64:
          return "base64";
       case xmlrpc_boolean:
          return "boolean";
       case xmlrpc_datetime:
          return "datetime";
       case xmlrpc_double:
          return "double";
       case xmlrpc_int:
          return "int";
       case xmlrpc_string:
          return "string";
       case xmlrpc_vector:
          switch(vtype) {
             case xmlrpc_vector_none:
                return "none";
             case xmlrpc_vector_array:
                return "array";
             case xmlrpc_vector_mixed:
                return "mixed vector (struct)";
             case xmlrpc_vector_struct:
                return "struct";
          }
    }
    return "unknown";
}