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
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ zval_get_i64 (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int64_t get_xclaim_i64_arg(const char *key, zval *zv) {
    int64_t retval = -1;

    /* Extract an i64, and if we can't let the user know there is an issue. */
    if (zval_get_i64(zv, &retval) == FAILURE || retval < 0) {
        php_error_docref(NULL, E_WARNING,
            "Invalid XCLAIM option '%s' will be ignored", key);
    }

    return retval;
}