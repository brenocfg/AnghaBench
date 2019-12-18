#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_1__* sdlSoapBindingPtr ;
typedef  TYPE_1__* sdlBindingPtr ;
struct TYPE_5__ {scalar_t__ bindingType; struct TYPE_5__* bindingAttributes; struct TYPE_5__* name; struct TYPE_5__* location; } ;

/* Variables and functions */
 scalar_t__ BINDING_SOAP ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void delete_binding_persistent(zval *zv)
{
	sdlBindingPtr binding = Z_PTR_P(zv);

	if (binding->location) {
		free(binding->location);
	}
	if (binding->name) {
		free(binding->name);
	}

	if (binding->bindingType == BINDING_SOAP) {
		sdlSoapBindingPtr soapBind = binding->bindingAttributes;
		if (soapBind) {
			free(soapBind);
		}
	}
	free(binding);
}