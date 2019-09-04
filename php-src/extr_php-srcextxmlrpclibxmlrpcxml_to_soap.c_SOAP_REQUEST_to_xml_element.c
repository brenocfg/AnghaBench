#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  children; void* name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ xml_element ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ XMLRPC_REQUEST_TYPE ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST ;

/* Variables and functions */
 scalar_t__ Q_Head (int /*<<< orphan*/ *) ; 
 scalar_t__ Q_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q_PushTail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ Q_Size (int /*<<< orphan*/ *) ; 
 TYPE_1__* SOAP_to_xml_element_worker (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOKEN_FAULT ; 
 int /*<<< orphan*/  XMLRPC_RequestGetData (int /*<<< orphan*/ ) ; 
 char* XMLRPC_RequestGetMethodName (int /*<<< orphan*/ ) ; 
 scalar_t__ XMLRPC_RequestGetRequestType (int /*<<< orphan*/ ) ; 
 void* estrdup (char const*) ; 
 TYPE_1__* new_attr (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  strcmp (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_elem_free_non_recurse (TYPE_1__*) ; 
 TYPE_1__* xml_elem_new () ; 
 scalar_t__ xmlrpc_request_call ; 

xml_element* SOAP_REQUEST_to_xml_element(XMLRPC_REQUEST request) {
	xml_element* root = xml_elem_new();

	/* safety first. */
	if (root) {
		xml_element* body = xml_elem_new();
		root->name = estrdup("SOAP-ENV:Envelope");

		/* silly namespace stuff */
		Q_PushTail(&root->attrs, new_attr("xmlns:SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/"));
		Q_PushTail(&root->attrs, new_attr("xmlns:xsi", "http://www.w3.org/1999/XMLSchema-instance"));
		Q_PushTail(&root->attrs, new_attr("xmlns:xsd", "http://www.w3.org/1999/XMLSchema"));
		Q_PushTail(&root->attrs, new_attr("xmlns:SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/"));
		Q_PushTail(&root->attrs, new_attr("xmlns:si", "http://soapinterop.org/xsd"));
		Q_PushTail(&root->attrs, new_attr("xmlns:ns6", "http://testuri.org"));
		Q_PushTail(&root->attrs, new_attr("SOAP-ENV:encodingStyle", "http://schemas.xmlsoap.org/soap/encoding/"));

		/* Q_PushHead(&root->attrs, new_attr("xmlns:ks", "http://kitchen.sink.org/soap/everything/under/sun"));
		       JUST KIDDING!! :-)  ---->                ------------------------------------------------- */

		if (body) {
			/* go ahead and serialize first... */
			xml_element* el_serialized =
			SOAP_to_xml_element_worker(request,
												XMLRPC_RequestGetData(request));

			/* check for fault, in which case, there is no intermediate element */
			if (el_serialized && !strcmp(el_serialized->name, TOKEN_FAULT)) {
				Q_PushTail(&body->children, el_serialized);
			}
			/* usual case: not a fault. Add Response element in between. */
			else {
				xml_element* rpc = xml_elem_new();

				if (rpc) {
					const char* methodname = XMLRPC_RequestGetMethodName(request);
					XMLRPC_REQUEST_TYPE rtype = XMLRPC_RequestGetRequestType(request);

					/* if we are making a request, we want to use the methodname as is. */
					if (rtype == xmlrpc_request_call) {
						if (methodname) {
							rpc->name = estrdup(methodname);
						}
					}
					/* if it's a response, we append "Response". Also, given xmlrpc-epi
					   API/architecture, it's likely that we don't have a methodname for
					   the response, so we have to check that. */
					else {
						char buf[128];
						snprintf(buf, sizeof(buf), "%s%s",
									methodname ? methodname : "",
									"Response");

						rpc->name = estrdup(buf);
					}

					/* add serialized data to method call/response.
					   add method call/response to body element */
					if (rpc->name) {
						if(el_serialized) {
							if(Q_Size(&el_serialized->children) && rtype == xmlrpc_request_call) {
								xml_element* iter = (xml_element*)Q_Head(&el_serialized->children);
								while(iter) {
									Q_PushTail(&rpc->children, iter);
									iter = (xml_element*)Q_Next(&el_serialized->children);
								}
								xml_elem_free_non_recurse(el_serialized);
							}
							else {
								Q_PushTail(&rpc->children, el_serialized);
							}
						}

						Q_PushTail(&body->children, rpc);
					}
					else {
						/* no method name?!
						   TODO: fault here...? */
					}
				}
			}
			body->name = estrdup("SOAP-ENV:Body");
			Q_PushTail(&root->children, body);
		}
	}

	return root;
}