#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ctxForeachCB {int /*<<< orphan*/  user; int /*<<< orphan*/  (* cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;TYPE_2__* anal; } ;
struct TYPE_9__ {int /*<<< orphan*/  zign_spaces; } ;
struct TYPE_8__ {int /*<<< orphan*/ * space; } ;
typedef  int /*<<< orphan*/  RSpace ;
typedef  TYPE_1__ RSignItem ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ r_sign_deserialize (TYPE_2__*,TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  r_sign_item_free (TYPE_1__*) ; 
 TYPE_1__* r_sign_item_new () ; 
 int /*<<< orphan*/ * r_spaces_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int foreachCB(void *user, const char *k, const char *v) {
	struct ctxForeachCB *ctx = (struct ctxForeachCB *) user;
	RSignItem *it = r_sign_item_new ();
	RAnal *a = ctx->anal;
	int retval = 1;

	if (r_sign_deserialize (a, it, k, v)) {
		RSpace *cur = r_spaces_current (&a->zign_spaces);
		if (ctx->cb && cur == it->space) {
			ctx->cb (it, ctx->user);
		}
	} else {
		eprintf ("error: cannot deserialize zign\n");
	}
	r_sign_item_free (it);
	return retval;
}