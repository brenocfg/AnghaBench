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
struct tun_struct {int /*<<< orphan*/  group; int /*<<< orphan*/  owner; int /*<<< orphan*/  dev; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct cred {int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 struct cred* current_cred () ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_egroup_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool tun_not_capable(struct tun_struct *tun)
{
	const struct cred *cred = current_cred();
	struct net *net = dev_net(tun->dev);

	return ((uid_valid(tun->owner) && !uid_eq(cred->euid, tun->owner)) ||
		  (gid_valid(tun->group) && !in_egroup_p(tun->group))) &&
		!ns_capable(net->user_ns, CAP_NET_ADMIN);
}