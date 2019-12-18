#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct print_flag_t {scalar_t__ range_from; scalar_t__ range_to; int /*<<< orphan*/  pj; scalar_t__ in_range; } ;
struct TYPE_3__ {scalar_t__ offset; int /*<<< orphan*/  comment; int /*<<< orphan*/  alias; int /*<<< orphan*/  size; int /*<<< orphan*/  realname; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RFlagItem ;

/* Variables and functions */
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pj_ki (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pj_kn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool print_flag_json(RFlagItem *flag, void *user) {
	struct print_flag_t *u = (struct print_flag_t *)user;
	if (u->in_range && (flag->offset < u->range_from || flag->offset >= u->range_to)) {
		return true;
	}
	pj_o (u->pj);
	pj_ks (u->pj, "name", flag->name);
	if (flag->name != flag->realname) {
		pj_ks (u->pj, "realname", flag->realname);
	}
	pj_ki (u->pj, "size", flag->size);
	if (flag->alias) {
		pj_ks (u->pj, "alias", flag->alias);
	} else {
		pj_kn (u->pj, "offset", flag->offset);
	}
	if (flag->comment) {
		pj_ks (u->pj, "comment", flag->comment);
	}
	pj_end (u->pj);
	return true;
}