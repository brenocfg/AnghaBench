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
typedef  scalar_t__ jsonsl_error_t ;

/* Variables and functions */
 scalar_t__ JSONSL_ERROR_SUCCESS ; 
 int /*<<< orphan*/  JSONSL_XERR ; 

const char* jsonsl_strerror(jsonsl_error_t err)
{
    if (err == JSONSL_ERROR_SUCCESS) {
        return "SUCCESS";
    }
#define X(t) \
    if (err == JSONSL_ERROR_##t) \
        return #t;
    JSONSL_XERR;
#undef X
    return "<UNKNOWN_ERROR>";
}