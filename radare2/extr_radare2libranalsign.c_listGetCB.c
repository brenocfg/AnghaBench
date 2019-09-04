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
struct ctxGetListCB {int /*<<< orphan*/  list; int /*<<< orphan*/  anal; } ;
typedef  int /*<<< orphan*/  RSignItem ;

/* Variables and functions */
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_sign_deserialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  r_sign_item_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_sign_item_new () ; 

__attribute__((used)) static int listGetCB(void *user, const char *key, const char *val) {
	struct ctxGetListCB *ctx = user;
	RSignItem *item = r_sign_item_new ();
	if (!item) {
		return false;
	}
	if (!r_sign_deserialize (ctx->anal, item, key, val)) {
		r_sign_item_free (item);
		return false;
	}
	r_list_append (ctx->list, item);

	return 1;
}