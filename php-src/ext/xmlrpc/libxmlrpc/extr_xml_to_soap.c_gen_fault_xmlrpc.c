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
typedef  int /*<<< orphan*/  xml_element ;
typedef  int /*<<< orphan*/  XMLRPC_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_SOAP_FAULTCODE ; 
 int /*<<< orphan*/  TOKEN_SOAP_FAULTSTRING ; 
 int /*<<< orphan*/  TOKEN_XMLRPC_FAULTCODE ; 
 int /*<<< orphan*/  TOKEN_XMLRPC_FAULTSTRING ; 
 int /*<<< orphan*/  XMLRPC_DupValueNew (int /*<<< orphan*/ ) ; 
 int XMLRPC_GetValueInt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueString (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_VectorGetValueWithID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static XMLRPC_VALUE gen_fault_xmlrpc(XMLRPC_VALUE node, xml_element* el_target) {
	XMLRPC_VALUE xDup = XMLRPC_DupValueNew(node);
	XMLRPC_VALUE xCode = XMLRPC_VectorGetValueWithID(xDup, TOKEN_XMLRPC_FAULTCODE);
	XMLRPC_VALUE xStr = XMLRPC_VectorGetValueWithID(xDup, TOKEN_XMLRPC_FAULTSTRING);

	XMLRPC_SetValueID(xCode, TOKEN_SOAP_FAULTCODE, 0);
	XMLRPC_SetValueID(xStr, TOKEN_SOAP_FAULTSTRING, 0);

	/* rough mapping of xmlrpc fault codes to soap codes */
	switch (XMLRPC_GetValueInt(xCode)) {
	case -32700:		  /* "parse error. not well formed", */
	case -32701:		  /* "parse error. unsupported encoding" */
	case -32702:		  /* "parse error. invalid character for encoding" */
	case -32600:		  /* "server error. invalid xml-rpc.  not conforming to spec." */
	case -32601:		  /* "server error. requested method not found" */
	case -32602:		  /* "server error. invalid method parameters" */
		XMLRPC_SetValueString(xCode, "SOAP-ENV:Client", 0);
		break;
	case -32603:		  /* "server error. internal xml-rpc error" */
	case -32500:		  /* "application error" */
	case -32400:		  /* "system error" */
	case -32300:		  /* "transport error */
		XMLRPC_SetValueString(xCode, "SOAP-ENV:Server", 0);
		break;
	}
	return xDup;
}