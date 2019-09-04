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
struct ctxUnsetForCB {TYPE_2__* anal; int /*<<< orphan*/ * space; } ;
struct TYPE_9__ {int /*<<< orphan*/ * sdb_zigns; } ;
struct TYPE_8__ {int /*<<< orphan*/ * space; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_1__ RSignItem ;

/* Variables and functions */
 int R_SIGN_KEY_MAXSZ ; 
 int R_SIGN_VAL_MAXSZ ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ r_sign_deserialize (TYPE_2__*,TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  r_sign_item_free (TYPE_1__*) ; 
 TYPE_1__* r_sign_item_new () ; 
 int /*<<< orphan*/  sdb_remove (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize (TYPE_2__*,TYPE_1__*,char*,char*) ; 

__attribute__((used)) static int unsetForCB(void *user, const char *k, const char *v) {
	struct ctxUnsetForCB *ctx = (struct ctxUnsetForCB *) user;
	char nk[R_SIGN_KEY_MAXSZ], nv[R_SIGN_VAL_MAXSZ];
	RSignItem *it = r_sign_item_new ();
	Sdb *db = ctx->anal->sdb_zigns;

	if (r_sign_deserialize (ctx->anal, it, k, v)) {
		if (it->space && it->space == ctx->space) {
			it->space = NULL;
			serialize (ctx->anal, it, nk, nv);
			sdb_remove (db, k, 0);
			sdb_set (db, nk, nv, 0);
		}
	} else {
		eprintf ("error: cannot deserialize zign\n");
	}
	r_sign_item_free (it);

	return 1;
}