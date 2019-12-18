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
struct ip_vs_conn {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  cport; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int IP_VS_CONN_F_NO_CPORT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_conn_hash (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_conn_no_cport_cnt ; 
 scalar_t__ ip_vs_conn_unhash (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ip_vs_conn_fill_cport(struct ip_vs_conn *cp, __be16 cport)
{
	if (ip_vs_conn_unhash(cp)) {
		spin_lock_bh(&cp->lock);
		if (cp->flags & IP_VS_CONN_F_NO_CPORT) {
			atomic_dec(&ip_vs_conn_no_cport_cnt);
			cp->flags &= ~IP_VS_CONN_F_NO_CPORT;
			cp->cport = cport;
		}
		spin_unlock_bh(&cp->lock);

		/* hash on new dport */
		ip_vs_conn_hash(cp);
	}
}