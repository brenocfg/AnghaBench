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
typedef  int /*<<< orphan*/  encodeTypePtr ;
struct TYPE_6__ {TYPE_1__* children; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ content; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  FIND_XML_NULL (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ XML_TEXT_NODE ; 
 int /*<<< orphan*/  ZVAL_FALSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ZVAL_TRUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_boolean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ stricmp (char*,char*) ; 
 int /*<<< orphan*/  whiteSpace_collapse (scalar_t__) ; 

__attribute__((used)) static zval *to_zval_bool(zval *ret, encodeTypePtr type, xmlNodePtr data)
{
	ZVAL_NULL(ret);
	FIND_XML_NULL(data, ret);

	if (data && data->children) {
		if (data->children->type == XML_TEXT_NODE && data->children->next == NULL) {
			whiteSpace_collapse(data->children->content);
			if (stricmp((char*)data->children->content, "true") == 0 ||
				stricmp((char*)data->children->content, "t") == 0 ||
				strcmp((char*)data->children->content, "1") == 0) {
				ZVAL_TRUE(ret);
			} else if (stricmp((char*)data->children->content, "false") == 0 ||
				stricmp((char*)data->children->content, "f") == 0 ||
				strcmp((char*)data->children->content, "0") == 0) {
				ZVAL_FALSE(ret);
			} else {
				ZVAL_STRING(ret, (char*)data->children->content);
				convert_to_boolean(ret);
			}
		} else {
			soap_error0(E_ERROR, "Encoding: Violation of encoding rules");
		}
	} else {
		ZVAL_NULL(ret);
	}
	return ret;
}