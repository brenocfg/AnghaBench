#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ctxCountForCB {scalar_t__ space; int /*<<< orphan*/  count; int /*<<< orphan*/  anal; } ;
struct TYPE_5__ {scalar_t__ space; } ;
typedef  TYPE_1__ RSignItem ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ r_sign_deserialize (int /*<<< orphan*/ ,TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  r_sign_item_free (TYPE_1__*) ; 
 TYPE_1__* r_sign_item_new () ; 

__attribute__((used)) static int countForCB(void *user, const char *k, const char *v) {
	struct ctxCountForCB *ctx = (struct ctxCountForCB *) user;
	RSignItem *it = r_sign_item_new ();

	if (r_sign_deserialize (ctx->anal, it, k, v)) {
		if (it->space == ctx->space) {
			ctx->count++;
		}
	} else {
		eprintf ("error: cannot deserialize zign\n");
	}
	r_sign_item_free (it);

	return 1;
}