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
struct xfrm_tmpl {int /*<<< orphan*/  encap_family; } ;
struct xfrm_policy {int xfrm_nr; struct xfrm_tmpl* xfrm_vec; int /*<<< orphan*/  family; } ;
struct sadb_x_policy {int dummy; } ;
struct sadb_x_ipsecrequest {int dummy; } ;
struct sadb_msg {int dummy; } ;
struct sadb_lifetime {int dummy; } ;
struct sadb_address {int dummy; } ;

/* Variables and functions */
 scalar_t__ pfkey_sockaddr_len (int /*<<< orphan*/ ) ; 
 int pfkey_sockaddr_size (int /*<<< orphan*/ ) ; 
 int pfkey_xfrm_policy2sec_ctx_size (struct xfrm_policy const*) ; 

__attribute__((used)) static int pfkey_xfrm_policy2msg_size(const struct xfrm_policy *xp)
{
	const struct xfrm_tmpl *t;
	int sockaddr_size = pfkey_sockaddr_size(xp->family);
	int socklen = 0;
	int i;

	for (i=0; i<xp->xfrm_nr; i++) {
		t = xp->xfrm_vec + i;
		socklen += pfkey_sockaddr_len(t->encap_family);
	}

	return sizeof(struct sadb_msg) +
		(sizeof(struct sadb_lifetime) * 3) +
		(sizeof(struct sadb_address) * 2) +
		(sockaddr_size * 2) +
		sizeof(struct sadb_x_policy) +
		(xp->xfrm_nr * sizeof(struct sadb_x_ipsecrequest)) +
		(socklen * 2) +
		pfkey_xfrm_policy2sec_ctx_size(xp);
}