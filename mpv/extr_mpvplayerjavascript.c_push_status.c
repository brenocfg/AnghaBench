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
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  mpv_error_string (int) ; 
 int /*<<< orphan*/  push_failure (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_success (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void push_status(js_State *J, int err)
{
    if (err >= 0) {
        push_success(J);
    } else {
        push_failure(J, mpv_error_string(err));
    }
}