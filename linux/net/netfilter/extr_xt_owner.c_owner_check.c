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
struct xt_owner_match_info {int match; scalar_t__ uid_min; scalar_t__ uid_max; scalar_t__ gid_min; scalar_t__ gid_max; } ;
struct xt_mtchk_param {struct net* net; struct xt_owner_match_info* matchinfo; } ;
struct net {scalar_t__ user_ns; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int EINVAL ; 
 int XT_OWNER_GID ; 
 int XT_OWNER_MASK ; 
 int XT_OWNER_UID ; 
 scalar_t__ current_user_ns () ; 
 scalar_t__ gid_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  make_kuid (scalar_t__,scalar_t__) ; 
 scalar_t__ uid_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int owner_check(const struct xt_mtchk_param *par)
{
	struct xt_owner_match_info *info = par->matchinfo;
	struct net *net = par->net;

	if (info->match & ~XT_OWNER_MASK)
		return -EINVAL;

	/* Only allow the common case where the userns of the writer
	 * matches the userns of the network namespace.
	 */
	if ((info->match & (XT_OWNER_UID|XT_OWNER_GID)) &&
	    (current_user_ns() != net->user_ns))
		return -EINVAL;

	/* Ensure the uids are valid */
	if (info->match & XT_OWNER_UID) {
		kuid_t uid_min = make_kuid(net->user_ns, info->uid_min);
		kuid_t uid_max = make_kuid(net->user_ns, info->uid_max);

		if (!uid_valid(uid_min) || !uid_valid(uid_max) ||
		    (info->uid_max < info->uid_min) ||
		    uid_lt(uid_max, uid_min)) {
			return -EINVAL;
		}
	}

	/* Ensure the gids are valid */
	if (info->match & XT_OWNER_GID) {
		kgid_t gid_min = make_kgid(net->user_ns, info->gid_min);
		kgid_t gid_max = make_kgid(net->user_ns, info->gid_max);

		if (!gid_valid(gid_min) || !gid_valid(gid_max) ||
		    (info->gid_max < info->gid_min) ||
		    gid_lt(gid_max, gid_min)) {
			return -EINVAL;
		}
	}

	return 0;
}