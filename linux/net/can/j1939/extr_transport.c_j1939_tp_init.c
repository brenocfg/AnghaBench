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
struct j1939_priv {int /*<<< orphan*/  tp_max_packet_size; int /*<<< orphan*/  active_session_list; int /*<<< orphan*/  active_session_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  J1939_MAX_ETP_PACKET_SIZE ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void j1939_tp_init(struct j1939_priv *priv)
{
	spin_lock_init(&priv->active_session_list_lock);
	INIT_LIST_HEAD(&priv->active_session_list);
	priv->tp_max_packet_size = J1939_MAX_ETP_PACKET_SIZE;
}