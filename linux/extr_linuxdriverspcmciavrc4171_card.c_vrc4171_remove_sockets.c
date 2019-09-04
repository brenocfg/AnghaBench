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
struct vrc4171_socket {scalar_t__ slot; int /*<<< orphan*/  pcmcia_socket; } ;

/* Variables and functions */
 int CARD_MAX_SLOTS ; 
 int CARD_SLOTB ; 
 scalar_t__ SLOTB_IS_NONE ; 
 scalar_t__ SLOT_INITIALIZED ; 
 scalar_t__ SLOT_PROBE ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (int /*<<< orphan*/ *) ; 
 scalar_t__ vrc4171_slotb ; 
 struct vrc4171_socket* vrc4171_sockets ; 

__attribute__((used)) static void vrc4171_remove_sockets(void)
{
	struct vrc4171_socket *socket;
	int slot;

	for (slot = 0; slot < CARD_MAX_SLOTS; slot++) {
		if (slot == CARD_SLOTB && vrc4171_slotb == SLOTB_IS_NONE)
			continue;

		socket = &vrc4171_sockets[slot];
		if (socket->slot == SLOT_INITIALIZED)
			pcmcia_unregister_socket(&socket->pcmcia_socket);

		socket->slot = SLOT_PROBE;
	}
}