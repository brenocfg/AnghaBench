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
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_basename (char const*) ; 
 TYPE_1__ mp_dirname (char const*) ; 

__attribute__((used)) static void script_split_path(js_State *J)
{
    const char *p = js_tostring(J, 1);
    bstr fname = mp_dirname(p);
    js_newarray(J);
    js_pushlstring(J, fname.start, fname.len);
    js_setindex(J, -2, 0);
    js_pushstring(J, mp_basename(p));
    js_setindex(J, -2, 1);
}