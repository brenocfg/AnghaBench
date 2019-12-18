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
typedef  double uint64_t ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 double UINT64_MAX ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*,int) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint64_t jsL_checkuint64(js_State *J, int idx)
{
    double d = js_tonumber(J, idx);
    if (!(d >= 0 && d <= UINT64_MAX))
        js_error(J, "uint64 out of range at index %d", idx);
    return d;
}