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
 int /*<<< orphan*/ * SOAP_to_xml_element_worker (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

xml_element* SOAP_VALUE_to_xml_element(XMLRPC_VALUE node) {
	return SOAP_to_xml_element_worker(NULL, node);
}