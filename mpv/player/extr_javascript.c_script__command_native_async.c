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
typedef  int /*<<< orphan*/  uint64_t ;
struct mpv_node {int dummy; } ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  jclient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsL_checkuint64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  makenode (void*,struct mpv_node*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpv_command_node_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mpv_node*) ; 
 int /*<<< orphan*/  push_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void script__command_native_async(js_State *J, void *af)
{
    uint64_t id = jsL_checkuint64(J, 1);
    struct mpv_node node;
    makenode(af, &node, J, 2);
    push_status(J, mpv_command_node_async(jclient(J), id, &node));
}