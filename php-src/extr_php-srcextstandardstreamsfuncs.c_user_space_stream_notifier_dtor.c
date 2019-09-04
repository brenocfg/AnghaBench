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
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ php_stream_notifier ;

/* Variables and functions */
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_space_stream_notifier_dtor(php_stream_notifier *notifier)
{
	if (notifier && Z_TYPE(notifier->ptr) != IS_UNDEF) {
		zval_ptr_dtor(&notifier->ptr);
		ZVAL_UNDEF(&notifier->ptr);
	}
}