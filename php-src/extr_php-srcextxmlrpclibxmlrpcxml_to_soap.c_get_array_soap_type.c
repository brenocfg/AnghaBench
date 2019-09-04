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
typedef  int XMLRPC_VALUE_TYPE_EASY ;
typedef  scalar_t__ XMLRPC_VALUE ;

/* Variables and functions */
 char* TOKEN_ANY ; 
 char* TOKEN_ARRAY ; 
 char* TOKEN_BASE64 ; 
 char* TOKEN_BOOLEAN ; 
 char* TOKEN_DATETIME ; 
 char* TOKEN_DOUBLE ; 
 char* TOKEN_INT ; 
 char* TOKEN_NULL ; 
 char* TOKEN_STRING ; 
 char* TOKEN_STRUCT ; 
 int XMLRPC_GetValueTypeEasy (scalar_t__) ; 
 scalar_t__ XMLRPC_VectorNext (scalar_t__) ; 
 scalar_t__ XMLRPC_VectorRewind (scalar_t__) ; 
#define  xmlrpc_type_array 138 
#define  xmlrpc_type_base64 137 
#define  xmlrpc_type_boolean 136 
#define  xmlrpc_type_datetime 135 
#define  xmlrpc_type_double 134 
#define  xmlrpc_type_empty 133 
#define  xmlrpc_type_int 132 
#define  xmlrpc_type_mixed 131 
#define  xmlrpc_type_none 130 
#define  xmlrpc_type_string 129 
#define  xmlrpc_type_struct 128 

__attribute__((used)) static const char* get_array_soap_type(XMLRPC_VALUE node) {
	XMLRPC_VALUE_TYPE_EASY type = xmlrpc_type_none;

	XMLRPC_VALUE xIter = XMLRPC_VectorRewind(node);
	int loopCount = 0;
	const char* soapType = TOKEN_ANY;

	type = XMLRPC_GetValueTypeEasy(xIter);
	xIter = XMLRPC_VectorNext(node);

	while (xIter) {
		/* 50 seems like a decent # of loops.  That will likely
		 * cover most cases.  Any more and we start to sacrifice
		 * performance.
		 */
		if ( (XMLRPC_GetValueTypeEasy(xIter) != type) || loopCount >= 50) {
			type = xmlrpc_type_none;
			break;
		}
		loopCount ++;

		xIter = XMLRPC_VectorNext(node);
	}
	switch (type) {
	case xmlrpc_type_none:
		soapType = TOKEN_ANY;
		break;
	case xmlrpc_type_empty:
		soapType = TOKEN_NULL;
		break;
	case xmlrpc_type_int:
		soapType = TOKEN_INT;
		break;
	case xmlrpc_type_double:
		soapType = TOKEN_DOUBLE;
		break;
	case xmlrpc_type_boolean:
		soapType = TOKEN_BOOLEAN;
		break;
	case xmlrpc_type_string:
		soapType = TOKEN_STRING;
		break;
	case xmlrpc_type_base64:
		soapType = TOKEN_BASE64;
		break;
	case xmlrpc_type_datetime:
		soapType = TOKEN_DATETIME;
		break;
	case xmlrpc_type_struct:
		soapType = TOKEN_STRUCT;
		break;
	case xmlrpc_type_array:
		soapType = TOKEN_ARRAY;
		break;
	case xmlrpc_type_mixed:
		soapType = TOKEN_STRUCT;
		break;
	}
	return soapType;
}