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
struct fwtty_port {int dummy; } ;
struct fwtty_peer {struct fwtty_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWPS_NOT_ATTACHED ; 
 int /*<<< orphan*/  peer_set_state (struct fwtty_peer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct fwtty_port *peer_revert_state(struct fwtty_peer *peer)
{
	struct fwtty_port *port = peer->port;

	peer->port = NULL;
	peer_set_state(peer, FWPS_NOT_ATTACHED);
	return port;
}