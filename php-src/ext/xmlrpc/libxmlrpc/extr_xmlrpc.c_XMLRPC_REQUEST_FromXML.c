#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ xml_element ;
typedef  TYPE_3__* XMLRPC_REQUEST_INPUT_OPTIONS ;
typedef  TYPE_4__* XMLRPC_REQUEST ;
struct TYPE_24__ {scalar_t__ parser_error; int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {int /*<<< orphan*/  version; } ;
struct TYPE_23__ {TYPE_1__ output; } ;
struct TYPE_22__ {int /*<<< orphan*/  xml_elem_opts; } ;
typedef  TYPE_5__ STRUCT_XML_ELEM_ERROR ;

/* Variables and functions */
 TYPE_4__* XMLRPC_RequestNew () ; 
 int /*<<< orphan*/  XMLRPC_RequestSetError (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_expat_errors (TYPE_5__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xml_elem_free (TYPE_2__*) ; 
 TYPE_2__* xml_elem_parse_buf (char const*,int,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  xml_element_to_DANDARPC_REQUEST (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xml_element_to_SOAP_REQUEST (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xml_element_to_XMLRPC_REQUEST (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xmlrpc_version_1_0 ; 
 int /*<<< orphan*/  xmlrpc_version_simple ; 
 int /*<<< orphan*/  xmlrpc_version_soap_1_1 ; 

XMLRPC_REQUEST XMLRPC_REQUEST_FromXML (const char *in_buf, int len,
													XMLRPC_REQUEST_INPUT_OPTIONS in_options) {
   XMLRPC_REQUEST request = XMLRPC_RequestNew();
   STRUCT_XML_ELEM_ERROR error = {0};

   if(request) {
		xml_element *root_elem =
		xml_elem_parse_buf (in_buf, len,
								  (in_options ? &in_options->xml_elem_opts : NULL),
								  &error);

      if(root_elem) {
         if(!strcmp(root_elem->name, "simpleRPC")) {
            request->output.version = xmlrpc_version_simple;
            xml_element_to_DANDARPC_REQUEST(request, root_elem);
         }
			else if (!strcmp (root_elem->name, "SOAP-ENV:Envelope")) {
				request->output.version = xmlrpc_version_soap_1_1;
				xml_element_to_SOAP_REQUEST (request, root_elem);
			}
         else {
            request->output.version = xmlrpc_version_1_0;
            xml_element_to_XMLRPC_REQUEST(request, root_elem);
         }
         xml_elem_free(root_elem);
      }
      else {
         if(error.parser_error) {
				XMLRPC_RequestSetError (request, map_expat_errors (&error));
         }
      }
   }

   return request;
}