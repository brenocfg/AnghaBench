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
struct TYPE_2__ {int /*<<< orphan*/  j; int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ ListJsonCtx ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_class_json (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int r_anal_class_list_json_cb(void *user, const char *k, const char *v) {
	ListJsonCtx *ctx = user;
	r_anal_class_json (ctx->anal, ctx->j, k);
	return 1;
}