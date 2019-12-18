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
struct j1939_sock {int /*<<< orphan*/  state; int /*<<< orphan*/ * priv; int /*<<< orphan*/  list; } ;
struct j1939_priv {int /*<<< orphan*/  j1939_socks_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  J1939_SOCK_BOUND ; 
 int /*<<< orphan*/  j1939_priv_put (struct j1939_priv*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void j1939_jsk_del(struct j1939_priv *priv, struct j1939_sock *jsk)
{
	spin_lock_bh(&priv->j1939_socks_lock);
	list_del_init(&jsk->list);
	spin_unlock_bh(&priv->j1939_socks_lock);

	jsk->priv = NULL;
	j1939_priv_put(priv);
	jsk->state &= ~J1939_SOCK_BOUND;
}