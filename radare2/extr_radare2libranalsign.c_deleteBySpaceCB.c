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
struct ctxDeleteCB {TYPE_1__* anal; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  sdb_zigns; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdb_remove (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int deleteBySpaceCB(void *user, const char *k, const char *v) {
	struct ctxDeleteCB *ctx = (struct ctxDeleteCB *) user;
	if (!strncmp (k, ctx->buf, strlen (ctx->buf))) {
		sdb_remove (ctx->anal->sdb_zigns, k, 0);
	}
	return 1;
}