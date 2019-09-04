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
struct TYPE_3__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ zend_resource ;
typedef  int /*<<< orphan*/  php_dispatchex ;

/* Variables and functions */
 int /*<<< orphan*/  disp_destructor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispatch_dtor(zend_resource *rsrc)
{
	php_dispatchex *disp = (php_dispatchex *)rsrc->ptr;
	disp_destructor(disp);
}