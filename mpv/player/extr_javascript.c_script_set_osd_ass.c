#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct script_ctx {TYPE_1__* mpctx; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_2__ {int /*<<< orphan*/  osd; } ;

/* Variables and functions */
 struct script_ctx* jctx (int /*<<< orphan*/ *) ; 
 int jsL_checkint (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_wakeup_core (TYPE_1__*) ; 
 int /*<<< orphan*/  osd_set_external (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  push_success (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void script_set_osd_ass(js_State *J)
{
    struct script_ctx *ctx = jctx(J);
    int res_x = jsL_checkint(J, 1);
    int res_y = jsL_checkint(J, 2);
    const char *text = js_tostring(J, 3);
    osd_set_external(ctx->mpctx->osd, ctx->client, res_x, res_y, (char *)text);
    mp_wakeup_core(ctx->mpctx);
    push_success(J);
}