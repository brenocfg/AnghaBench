#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlBufferPtr ;
typedef  int /*<<< orphan*/  encodeTypePtr ;
struct TYPE_6__ {TYPE_1__* children; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ content; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  FIND_XML_NULL (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 scalar_t__ XML_CDATA_SECTION_NODE ; 
 scalar_t__ XML_TEXT_NODE ; 
 int /*<<< orphan*/  ZVAL_EMPTY_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  encoding ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  whiteSpace_replace (scalar_t__) ; 
 scalar_t__ xmlBufferContent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferCreateStatic (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlBufferFree (int /*<<< orphan*/ ) ; 
 int xmlCharEncOutFunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlStrlen (scalar_t__) ; 

__attribute__((used)) static zval *to_zval_stringr(zval *ret, encodeTypePtr type, xmlNodePtr data)
{
	ZVAL_NULL(ret);
	FIND_XML_NULL(data, ret);
	if (data && data->children) {
		if (data->children->type == XML_TEXT_NODE && data->children->next == NULL) {
			whiteSpace_replace(data->children->content);
			if (SOAP_GLOBAL(encoding) != NULL) {
				xmlBufferPtr in  = xmlBufferCreateStatic(data->children->content, xmlStrlen(data->children->content));
				xmlBufferPtr out = xmlBufferCreate();
				int n = xmlCharEncOutFunc(SOAP_GLOBAL(encoding), out, in);

				if (n >= 0) {
					ZVAL_STRING(ret, (char*)xmlBufferContent(out));
				} else {
					ZVAL_STRING(ret, (char*)data->children->content);
				}
				xmlBufferFree(out);
				xmlBufferFree(in);
			} else {
				ZVAL_STRING(ret, (char*)data->children->content);
			}
		} else if (data->children->type == XML_CDATA_SECTION_NODE && data->children->next == NULL) {
			ZVAL_STRING(ret, (char*)data->children->content);
		} else {
			soap_error0(E_ERROR, "Encoding: Violation of encoding rules");
		}
	} else {
		ZVAL_EMPTY_STRING(ret);
	}
	return ret;
}