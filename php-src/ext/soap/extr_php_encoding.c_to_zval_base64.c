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
typedef  int /*<<< orphan*/  zend_string ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  encodeTypePtr ;
struct TYPE_6__ {TYPE_1__* children; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ content; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  FIND_XML_NULL (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ XML_CDATA_SECTION_NODE ; 
 scalar_t__ XML_TEXT_NODE ; 
 int /*<<< orphan*/  ZVAL_EMPTY_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_base64_decode (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  whiteSpace_collapse (scalar_t__) ; 

__attribute__((used)) static zval *to_zval_base64(zval *ret, encodeTypePtr type, xmlNodePtr data)
{
	zend_string *str;

	ZVAL_NULL(ret);
	FIND_XML_NULL(data, ret);
	if (data && data->children) {
		if (data->children->type == XML_TEXT_NODE && data->children->next == NULL) {
			whiteSpace_collapse(data->children->content);
			str = php_base64_decode(data->children->content, strlen((char*)data->children->content));
			if (!str) {
				soap_error0(E_ERROR, "Encoding: Violation of encoding rules");
			}
			ZVAL_STR(ret, str);
		} else if (data->children->type == XML_CDATA_SECTION_NODE && data->children->next == NULL) {
			str = php_base64_decode(data->children->content, strlen((char*)data->children->content));
			if (!str) {
				soap_error0(E_ERROR, "Encoding: Violation of encoding rules");
			}
			ZVAL_STR(ret, str);
		} else {
			soap_error0(E_ERROR, "Encoding: Violation of encoding rules");
		}
	} else {
		ZVAL_EMPTY_STRING(ret);
	}
	return ret;
}