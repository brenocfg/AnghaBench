#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlNodePtr ;
typedef  TYPE_4__* xmlAttrPtr ;
struct TYPE_10__ {TYPE_1__* children; } ;
struct TYPE_9__ {TYPE_2__* ns; int /*<<< orphan*/  properties; } ;
struct TYPE_8__ {scalar_t__ href; } ;
struct TYPE_7__ {scalar_t__ content; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 char* WSDL_NAMESPACE ; 
 TYPE_4__* get_attribute_ex (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int is_wsdl_element(xmlNodePtr node)
{
	if (node->ns && strcmp((char*)node->ns->href, WSDL_NAMESPACE) != 0) {
		xmlAttrPtr attr;
		if ((attr = get_attribute_ex(node->properties, "required", WSDL_NAMESPACE)) != NULL &&
		     attr->children && attr->children->content &&
		     (strcmp((char*)attr->children->content, "1") == 0 ||
		      strcmp((char*)attr->children->content, "true") == 0)) {
			soap_error1(E_ERROR, "Parsing WSDL: Unknown required WSDL extension '%s'", node->ns->href);
		}
		return 0;
	}
	return 1;
}