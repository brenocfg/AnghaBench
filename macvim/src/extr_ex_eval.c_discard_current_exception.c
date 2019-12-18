#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/ * current_exception ; 
 void* did_throw ; 
 int /*<<< orphan*/  discard_exception (int /*<<< orphan*/ *,void*) ; 
 void* need_rethrow ; 

void
discard_current_exception()
{
    discard_exception(current_exception, FALSE);
    current_exception = NULL;
    did_throw = FALSE;
    need_rethrow = FALSE;
}