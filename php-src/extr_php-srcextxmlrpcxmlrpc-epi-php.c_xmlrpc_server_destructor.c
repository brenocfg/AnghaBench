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
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ zend_resource ;
typedef  int /*<<< orphan*/  xmlrpc_server_data ;

/* Variables and functions */
 int /*<<< orphan*/  GC_ADDREF (TYPE_1__*) ; 
 int /*<<< orphan*/  GC_DELREF (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_server_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xmlrpc_server_destructor(zend_resource *rsrc)
{
	if (rsrc && rsrc->ptr) {
		GC_ADDREF(rsrc);
		destroy_server_data((xmlrpc_server_data*) rsrc->ptr);
		GC_DELREF(rsrc);
	}
}