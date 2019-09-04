#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ headers; scalar_t__ ns; } ;
typedef  TYPE_1__ sdlSoapBindingFunctionBody ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  zend_hash_destroy (scalar_t__) ; 

__attribute__((used)) static void delete_sdl_soap_binding_function_body_persistent(sdlSoapBindingFunctionBody body)
{
	if (body.ns) {
		free(body.ns);
	}
	if (body.headers) {
		zend_hash_destroy(body.headers);
		free(body.headers);
	}
}