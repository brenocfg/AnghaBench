#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ctx; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ myMetaUser ;
struct TYPE_8__ {scalar_t__ space; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  anal; TYPE_1__* user; } ;
typedef  TYPE_2__ RAnalMetaUserItem ;
typedef  TYPE_3__ RAnalMetaItem ;

/* Variables and functions */
 int /*<<< orphan*/  meta_deserialize (int /*<<< orphan*/ ,TYPE_3__*,char const*,char const*) ; 
 int /*<<< orphan*/  r_meta_item_fini (TYPE_3__*) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

__attribute__((used)) static int meta_count_cb(void *user, const char *k, const char *v) {
	RAnalMetaUserItem *ui = user;
	myMetaUser *mu = ui->user;
	RAnalMetaItem it = {0};
	if (!strstr (k, ".0x")) {
		return 1;
	}
	meta_deserialize (ui->anal, &it, k, v);
	if (mu && it.space == mu->ctx) {
		mu->count++;
	}
	r_meta_item_fini (&it);
	return 1;
}