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
 int /*<<< orphan*/ * XMLRPC_VALUE_to_xml_element (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_elem_free (int /*<<< orphan*/ *) ; 
 char* xml_elem_serialize_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

char* XMLRPC_VALUE_ToXML(XMLRPC_VALUE val, int* buf_len) {
   xml_element *root_elem = XMLRPC_VALUE_to_xml_element(val);
   char* pRet = NULL;

   if(root_elem) {
      pRet = xml_elem_serialize_to_string(root_elem, NULL, buf_len);
      xml_elem_free(root_elem);
   }
   return pRet;
}