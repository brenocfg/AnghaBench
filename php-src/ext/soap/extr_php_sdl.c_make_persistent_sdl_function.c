#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sdlSoapBindingFunctionPtr ;
typedef  int /*<<< orphan*/  sdlSoapBindingFunction ;
typedef  TYPE_1__* sdlFunctionPtr ;
typedef  int /*<<< orphan*/  sdlFunction ;
typedef  TYPE_3__* sdlBindingPtr ;
struct TYPE_11__ {scalar_t__ bindingType; } ;
struct TYPE_10__ {scalar_t__ faults; void* responseParameters; void* requestParameters; struct TYPE_10__* bindingAttributes; int /*<<< orphan*/  output; int /*<<< orphan*/  input; void* soapAction; TYPE_3__* binding; void* responseName; void* requestName; void* functionName; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ BINDING_SOAP ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ make_persistent_sdl_function_faults (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 void* make_persistent_sdl_parameters (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_persistent_sdl_soap_body (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* strdup (void*) ; 
 TYPE_3__* zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static sdlFunctionPtr make_persistent_sdl_function(sdlFunctionPtr func, HashTable *ptr_map)
{
	sdlFunctionPtr pfunc = NULL;

	pfunc = malloc(sizeof(sdlFunction));
	memset(pfunc, 0, sizeof(sdlFunction));

	*pfunc = *func;

	if (pfunc->functionName) {
		pfunc->functionName = strdup(pfunc->functionName);
	}
	if (pfunc->requestName) {
		pfunc->requestName = strdup(pfunc->requestName);
	}
	if (pfunc->responseName) {
		pfunc->responseName = strdup(pfunc->responseName);
	}

	if (pfunc->binding) {
		sdlBindingPtr tmp;

		if ((tmp = zend_hash_str_find_ptr(ptr_map, (char*)&pfunc->binding, sizeof(pfunc->binding))) == NULL) {
			assert(0);
		}
		pfunc->binding = tmp;

		if (pfunc->binding->bindingType == BINDING_SOAP && pfunc->bindingAttributes) {
			sdlSoapBindingFunctionPtr soap_binding;

		   	soap_binding = malloc(sizeof(sdlSoapBindingFunction));
			memset(soap_binding, 0, sizeof(sdlSoapBindingFunction));
			*soap_binding = *(sdlSoapBindingFunctionPtr)pfunc->bindingAttributes;
			if (soap_binding->soapAction) {
				soap_binding->soapAction = strdup(soap_binding->soapAction);
			}
			make_persistent_sdl_soap_body(&soap_binding->input, ptr_map);
			make_persistent_sdl_soap_body(&soap_binding->output, ptr_map);
			pfunc->bindingAttributes = soap_binding;
		}

		if (pfunc->requestParameters) {
			pfunc->requestParameters = make_persistent_sdl_parameters(pfunc->requestParameters, ptr_map);
		}
		if (pfunc->responseParameters) {
			pfunc->responseParameters = make_persistent_sdl_parameters(pfunc->responseParameters, ptr_map);
		}
		if (pfunc->faults) {
			pfunc->faults = make_persistent_sdl_function_faults(pfunc, pfunc->faults, ptr_map);
		}
	}

	return pfunc;
}