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
typedef  int /*<<< orphan*/  XMLRPC_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_FAULT ; 
 int /*<<< orphan*/  TOKEN_SOAP_FAULTACTOR ; 
 int /*<<< orphan*/  TOKEN_SOAP_FAULTCODE ; 
 int /*<<< orphan*/  TOKEN_SOAP_FAULTDETAILS ; 
 int /*<<< orphan*/  TOKEN_SOAP_FAULTSTRING ; 
 int /*<<< orphan*/  XMLRPC_AddValuesToVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_CreateValueString (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_CreateVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlrpc_vector_struct ; 

__attribute__((used)) static XMLRPC_VALUE gen_soap_fault(const char* fault_code, const char* fault_string,
											  const char* actor, const char* details) {
	XMLRPC_VALUE xReturn = XMLRPC_CreateVector(TOKEN_FAULT, xmlrpc_vector_struct);
	XMLRPC_AddValuesToVector(xReturn,
									 XMLRPC_CreateValueString(TOKEN_SOAP_FAULTCODE, fault_code, 0),
									 XMLRPC_CreateValueString(TOKEN_SOAP_FAULTSTRING, fault_string, 0),
									 XMLRPC_CreateValueString(TOKEN_SOAP_FAULTACTOR, actor, 0),
									 XMLRPC_CreateValueString(TOKEN_SOAP_FAULTDETAILS, details, 0),
									 NULL);
	return xReturn;
}