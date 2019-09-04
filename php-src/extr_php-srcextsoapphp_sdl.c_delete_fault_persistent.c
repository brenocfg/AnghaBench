#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_1__* sdlSoapBindingFunctionFaultPtr ;
typedef  TYPE_2__* sdlFaultPtr ;
struct TYPE_7__ {struct TYPE_7__* bindingAttributes; struct TYPE_7__* details; struct TYPE_7__* name; } ;
struct TYPE_6__ {TYPE_2__* ns; } ;

/* Variables and functions */
 TYPE_2__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (TYPE_2__*) ; 

__attribute__((used)) static void delete_fault_persistent(zval *zv)
{
	sdlFaultPtr fault = Z_PTR_P(zv);
	if (fault->name) {
		free(fault->name);
	}
	if (fault->details) {
		zend_hash_destroy(fault->details);
		free(fault->details);
	}
	if (fault->bindingAttributes) {
		sdlSoapBindingFunctionFaultPtr binding = (sdlSoapBindingFunctionFaultPtr)fault->bindingAttributes;

		if (binding->ns) {
			free(binding->ns);
		}
		free(fault->bindingAttributes);
	}
	free(fault);
}