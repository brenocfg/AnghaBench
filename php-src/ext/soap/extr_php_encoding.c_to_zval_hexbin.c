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
struct TYPE_5__ {scalar_t__ type; unsigned char* content; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  FIND_XML_NULL (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ XML_CDATA_SECTION_NODE ; 
 scalar_t__ XML_TEXT_NODE ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 unsigned char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_EMPTY_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  whiteSpace_collapse (unsigned char*) ; 
 int /*<<< orphan*/ * zend_string_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *to_zval_hexbin(zval *ret, encodeTypePtr type, xmlNodePtr data)
{
	zend_string *str;
	size_t i, j;
	unsigned char c;

	ZVAL_NULL(ret);
	FIND_XML_NULL(data, ret);
	if (data && data->children) {
		if (data->children->type == XML_TEXT_NODE && data->children->next == NULL) {
			whiteSpace_collapse(data->children->content);
		} else if (data->children->type != XML_CDATA_SECTION_NODE || data->children->next != NULL) {
			soap_error0(E_ERROR, "Encoding: Violation of encoding rules");
			return ret;
		}
		str = zend_string_alloc(strlen((char*)data->children->content) / 2, 0);
		for (i = j = 0; i < ZSTR_LEN(str); i++) {
			c = data->children->content[j++];
			if (c >= '0' && c <= '9') {
				ZSTR_VAL(str)[i] = (c - '0') << 4;
			} else if (c >= 'a' && c <= 'f') {
				ZSTR_VAL(str)[i] = (c - 'a' + 10) << 4;
			} else if (c >= 'A' && c <= 'F') {
				ZSTR_VAL(str)[i] = (c - 'A' + 10) << 4;
			} else {
				soap_error0(E_ERROR, "Encoding: Violation of encoding rules");
			}
			c = data->children->content[j++];
			if (c >= '0' && c <= '9') {
				ZSTR_VAL(str)[i] |= c - '0';
			} else if (c >= 'a' && c <= 'f') {
				ZSTR_VAL(str)[i] |= c - 'a' + 10;
			} else if (c >= 'A' && c <= 'F') {
				ZSTR_VAL(str)[i] |= c - 'A' + 10;
			} else {
				soap_error0(E_ERROR, "Encoding: Violation of encoding rules");
			}
		}
		ZSTR_VAL(str)[ZSTR_LEN(str)] = '\0';
		ZVAL_NEW_STR(ret, str);
	} else {
		ZVAL_EMPTY_STRING(ret);
	}
	return ret;
}