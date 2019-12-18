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
typedef  int /*<<< orphan*/  mpv_node ;
typedef  int /*<<< orphan*/  mpv_handle ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_NODE ; 
 int /*<<< orphan*/ * jclient (int /*<<< orphan*/ *) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int mpv_get_property (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_af_mpv_node (void*) ; 
 int /*<<< orphan*/  pushed_error (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pushnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void script_get_property_native(js_State *J, void *af)
{
    const char *name = js_tostring(J, 1);
    mpv_handle *h = jclient(J);
    mpv_node *presult_node = new_af_mpv_node(af);
    int e = mpv_get_property(h, name, MPV_FORMAT_NODE, presult_node);
    if (!pushed_error(J, e, 2))
        pushnode(J, presult_node);
}