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
struct isi_port {int dummy; } ;
struct isi_board {int status; int port_count; struct isi_port* ports; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int BOARD_ACTIVE ; 
 int BOARD_INIT ; 
 int /*<<< orphan*/  drop_dtr_rts (struct isi_port*) ; 

__attribute__((used)) static inline void isicom_setup_board(struct isi_board *bp)
{
	int channel;
	struct isi_port *port;

	bp->count++;
	if (!(bp->status & BOARD_INIT)) {
		port = bp->ports;
		for (channel = 0; channel < bp->port_count; channel++, port++)
			drop_dtr_rts(port);
	}
	bp->status |= BOARD_ACTIVE | BOARD_INIT;
}