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
struct ctxRenameForCB {char* nprefix; int /*<<< orphan*/  oprefix; TYPE_1__* anal; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sdb_zigns; } ;
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 int R_SIGN_KEY_MAXSZ ; 
 int R_SIGN_VAL_MAXSZ ; 
 int /*<<< orphan*/  sdb_remove (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int renameForCB(void *user, const char *k, const char *v) {
	struct ctxRenameForCB *ctx = (struct ctxRenameForCB *) user;
	char nk[R_SIGN_KEY_MAXSZ], nv[R_SIGN_VAL_MAXSZ];
	const char *zigname = NULL;
	Sdb *db = ctx->anal->sdb_zigns;

	if (!strncmp (k, ctx->oprefix, strlen (ctx->oprefix))) {
		zigname = k + strlen (ctx->oprefix);
		snprintf (nk, R_SIGN_KEY_MAXSZ, "%s%s", ctx->nprefix, zigname);
		snprintf (nv, R_SIGN_VAL_MAXSZ, "%s", v);
		sdb_remove (db, k, 0);
		sdb_set (db, nk, nv, 0);
	}

	return 1;
}