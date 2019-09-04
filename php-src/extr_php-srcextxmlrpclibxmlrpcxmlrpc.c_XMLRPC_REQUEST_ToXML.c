#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_element ;
typedef  TYPE_2__* XMLRPC_REQUEST ;
struct TYPE_7__ {scalar_t__ version; int /*<<< orphan*/  xml_elem_opts; } ;
struct TYPE_8__ {TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DANDARPC_REQUEST_to_xml_element (TYPE_2__*) ; 
 int /*<<< orphan*/ * SOAP_REQUEST_to_xml_element (TYPE_2__*) ; 
 int /*<<< orphan*/ * XMLRPC_REQUEST_to_xml_element (TYPE_2__*) ; 
 int /*<<< orphan*/  xml_elem_free (int /*<<< orphan*/ *) ; 
 char* xml_elem_serialize_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ xmlrpc_version_1_0 ; 
 scalar_t__ xmlrpc_version_none ; 
 scalar_t__ xmlrpc_version_simple ; 
 scalar_t__ xmlrpc_version_soap_1_1 ; 

char* XMLRPC_REQUEST_ToXML(XMLRPC_REQUEST request, int* buf_len) {
      char* pRet = NULL;
	if (request) {
		xml_element *root_elem = NULL;
		if (request->output.version == xmlrpc_version_simple) {
			root_elem = DANDARPC_REQUEST_to_xml_element (request);
		}
		else if (request->output.version == xmlrpc_version_1_0 ||
					request->output.version == xmlrpc_version_none) {
			root_elem = XMLRPC_REQUEST_to_xml_element (request);
		}
		else if (request->output.version == xmlrpc_version_soap_1_1) {
			root_elem = SOAP_REQUEST_to_xml_element (request);
		}

      if(root_elem) {
			pRet =
			xml_elem_serialize_to_string (root_elem,
													&request->output.xml_elem_opts,
													buf_len);
         xml_elem_free(root_elem);
      }
   }
	return pRet;
}