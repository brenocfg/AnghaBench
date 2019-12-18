#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; scalar_t__ str; int /*<<< orphan*/  from; } ;
struct TYPE_4__ {scalar_t__ fcn; int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RAnalMetaUserItem ;
typedef  TYPE_2__ RAnalMetaItem ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  meta_deserialize (int /*<<< orphan*/ ,TYPE_2__*,char const*,char const*) ; 
 int /*<<< orphan*/  r_anal_fcn_in (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strdup (char*) ; 

__attribute__((used)) static int get_meta_size(void *user, const char *k, const char *v) {
	RAnalMetaUserItem *ui = user;
	RAnalMetaItem it;
	if (!meta_deserialize (ui->anal, &it, k, v)) {
		return -1;
	}
	if (ui->fcn && !r_anal_fcn_in (ui->fcn, it.from)) {
		goto beach;
	}
	if (!it.str) {
		it.str = strdup (""); // don't break in free
		if (!it.str) {
			goto beach;
		}
	}
	return it.size;
beach:
	free (it.str);
	return -1;
}