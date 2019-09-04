#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  TYPE_3__* xmlDocPtr ;
typedef  TYPE_4__* encodeTypePtr ;
struct TYPE_19__ {TYPE_1__* map; } ;
struct TYPE_18__ {scalar_t__ children; } ;
struct TYPE_17__ {int /*<<< orphan*/  doc; } ;
struct TYPE_16__ {int /*<<< orphan*/  to_xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 scalar_t__ FAILURE ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ IS_UNDEF ; 
 int SOAP_ENCODED ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_ns_and_type (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* soap_xmlParseMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlAddChild (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* xmlDocCopyNode (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmlFreeDoc (TYPE_3__*) ; 
 TYPE_2__* xmlNewNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

xmlNodePtr to_xml_user(encodeTypePtr type, zval *data, int style, xmlNodePtr parent)
{
	xmlNodePtr ret = NULL;
	zval return_value;

	if (type && type->map && Z_TYPE(type->map->to_xml) != IS_UNDEF) {
		ZVAL_NULL(&return_value);

		if (call_user_function(NULL, NULL, &type->map->to_xml, &return_value, 1, data) == FAILURE) {
			soap_error0(E_ERROR, "Encoding: Error calling to_xml callback");
		}
		if (Z_TYPE(return_value) == IS_STRING) {
			xmlDocPtr doc = soap_xmlParseMemory(Z_STRVAL(return_value), Z_STRLEN(return_value));
			if (doc && doc->children) {
				ret = xmlDocCopyNode(doc->children, parent->doc, 1);
			}
			xmlFreeDoc(doc);
		}

		zval_ptr_dtor(&return_value);
	}
	if (!ret) {
		ret = xmlNewNode(NULL, BAD_CAST("BOGUS"));
	}
	xmlAddChild(parent, ret);
	if (style == SOAP_ENCODED) {
		set_ns_and_type(ret, type);
	}
	return ret;
}