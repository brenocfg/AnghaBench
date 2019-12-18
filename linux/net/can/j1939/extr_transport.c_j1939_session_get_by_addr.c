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
struct j1939_session {int dummy; } ;
struct j1939_priv {int /*<<< orphan*/  active_session_list; } ;
struct j1939_addr {int dummy; } ;

/* Variables and functions */
 struct j1939_session* j1939_session_get_by_addr_locked (struct j1939_priv*,int /*<<< orphan*/ *,struct j1939_addr*,int,int) ; 
 int /*<<< orphan*/  j1939_session_list_lock (struct j1939_priv*) ; 
 int /*<<< orphan*/  j1939_session_list_unlock (struct j1939_priv*) ; 

__attribute__((used)) static struct
j1939_session *j1939_session_get_by_addr(struct j1939_priv *priv,
					 struct j1939_addr *addr,
					 bool reverse, bool transmitter)
{
	struct j1939_session *session;

	j1939_session_list_lock(priv);
	session = j1939_session_get_by_addr_locked(priv,
						   &priv->active_session_list,
						   addr, reverse, transmitter);
	j1939_session_list_unlock(priv);

	return session;
}