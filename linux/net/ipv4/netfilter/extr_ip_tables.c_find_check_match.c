#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_mtchk_param {int dummy; } ;
struct xt_match {int /*<<< orphan*/  me; } ;
struct TYPE_5__ {struct xt_match* match; } ;
struct TYPE_4__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ kernel; TYPE_1__ user; } ;
struct xt_entry_match {TYPE_3__ u; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct xt_match*) ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int PTR_ERR (struct xt_match*) ; 
 int check_match (struct xt_entry_match*,struct xt_mtchk_param*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct xt_match* xt_request_find_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_check_match(struct xt_entry_match *m, struct xt_mtchk_param *par)
{
	struct xt_match *match;
	int ret;

	match = xt_request_find_match(NFPROTO_IPV4, m->u.user.name,
				      m->u.user.revision);
	if (IS_ERR(match))
		return PTR_ERR(match);
	m->u.kernel.match = match;

	ret = check_match(m, par);
	if (ret)
		goto err;

	return 0;
err:
	module_put(m->u.kernel.match->me);
	return ret;
}