#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sdlSoapBindingPtr ;
typedef  int /*<<< orphan*/  sdlSoapBinding ;
typedef  TYPE_1__* sdlBindingPtr ;
typedef  int /*<<< orphan*/  sdlBinding ;
struct TYPE_7__ {scalar_t__ bindingType; struct TYPE_7__* bindingAttributes; void* location; void* name; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ BINDING_SOAP ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* strdup (void*) ; 

__attribute__((used)) static sdlBindingPtr make_persistent_sdl_binding(sdlBindingPtr bind, HashTable *ptr_map)
{
	sdlBindingPtr pbind = NULL;

	pbind = malloc(sizeof(sdlBinding));
	memset(pbind, 0, sizeof(sdlBinding));

	*pbind = *bind;

	if (pbind->name) {
		pbind->name = strdup(pbind->name);
	}
	if (pbind->location) {
		pbind->location = strdup(pbind->location);
	}

	if (pbind->bindingType == BINDING_SOAP && pbind->bindingAttributes) {
		sdlSoapBindingPtr soap_binding;

		soap_binding = malloc(sizeof(sdlSoapBinding));
		memset(soap_binding, 0, sizeof(sdlSoapBinding));
		*soap_binding = *(sdlSoapBindingPtr)pbind->bindingAttributes;
		pbind->bindingAttributes = soap_binding;
	}

	return pbind;
}