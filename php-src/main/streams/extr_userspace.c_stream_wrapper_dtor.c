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
struct php_user_stream_wrapper {struct php_user_stream_wrapper* classname; struct php_user_stream_wrapper* protoname; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (struct php_user_stream_wrapper*) ; 

__attribute__((used)) static void stream_wrapper_dtor(zend_resource *rsrc)
{
	struct php_user_stream_wrapper * uwrap = (struct php_user_stream_wrapper*)rsrc->ptr;

	efree(uwrap->protoname);
	efree(uwrap->classname);
	efree(uwrap);
}