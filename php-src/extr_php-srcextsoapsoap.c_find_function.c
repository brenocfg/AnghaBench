#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  TYPE_3__* sdlSoapBindingFunctionPtr ;
typedef  int /*<<< orphan*/ * sdlPtr ;
typedef  TYPE_4__* sdlFunctionPtr ;
struct TYPE_13__ {scalar_t__ functionName; int /*<<< orphan*/ * requestParameters; int /*<<< orphan*/  bindingAttributes; TYPE_1__* binding; } ;
struct TYPE_12__ {scalar_t__ style; } ;
struct TYPE_11__ {scalar_t__ name; int /*<<< orphan*/ * children; } ;
struct TYPE_10__ {scalar_t__ bindingType; } ;

/* Variables and functions */
 scalar_t__ BINDING_SOAP ; 
 scalar_t__ SOAP_DOCUMENT ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* get_doc_function (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_4__* get_function (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sdlFunctionPtr find_function(sdlPtr sdl, xmlNodePtr func, zval* function_name) /* {{{ */
{
	sdlFunctionPtr function;

	function = get_function(sdl, (char*)func->name);
	if (function && function->binding && function->binding->bindingType == BINDING_SOAP) {
		sdlSoapBindingFunctionPtr fnb = (sdlSoapBindingFunctionPtr)function->bindingAttributes;
		if (fnb->style == SOAP_DOCUMENT) {
			if (func->children != NULL ||
			    (function->requestParameters != NULL &&
			     zend_hash_num_elements(function->requestParameters) > 0)) {
				function = NULL;
			}
		}
	}
	if (sdl != NULL && function == NULL) {
		function = get_doc_function(sdl, func);
	}

	if (function != NULL) {
		ZVAL_STRING(function_name, (char *)function->functionName);
	} else {
		ZVAL_STRING(function_name, (char *)func->name);
	}

	return function;
}