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
typedef  double int64_t ;

/* Variables and functions */
 double INT64_MAX ; 
 double INT64_MIN ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*,int) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int64_t jsL_checkint64(js_State *J, int idx)
{
    double d = js_tonumber(J, idx);
    if (!(d >= INT64_MIN && d <= INT64_MAX))
        js_error(J, "integer out of range at index %d", idx);
    return d;
}