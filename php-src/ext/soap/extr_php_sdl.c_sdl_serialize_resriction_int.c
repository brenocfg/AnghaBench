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
typedef  int /*<<< orphan*/  smart_str ;
typedef  TYPE_1__* sdlRestrictionIntPtr ;
struct TYPE_3__ {int fixed; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  WSDL_CACHE_PUT_1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WSDL_CACHE_PUT_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdl_serialize_resriction_int(sdlRestrictionIntPtr x, smart_str *out)
{
	if (x) {
		WSDL_CACHE_PUT_1(1, out);
		WSDL_CACHE_PUT_INT(x->value, out);
		WSDL_CACHE_PUT_1(x->fixed, out);
	} else {
		WSDL_CACHE_PUT_1(0, out);
	}
}