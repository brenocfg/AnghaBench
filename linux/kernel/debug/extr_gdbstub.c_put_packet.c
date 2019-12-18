#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* flush ) () ;int /*<<< orphan*/  (* write_char ) (char) ;} ;

/* Variables and functions */
 TYPE_1__* dbg_io_ops ; 
 char gdbstub_read_wait () ; 
 char hex_asc_hi (unsigned char) ; 
 char hex_asc_lo (unsigned char) ; 
 int /*<<< orphan*/  stub1 (char) ; 
 int /*<<< orphan*/  stub2 (char) ; 
 int /*<<< orphan*/  stub3 (char) ; 
 int /*<<< orphan*/  stub4 (char) ; 
 int /*<<< orphan*/  stub5 (char) ; 
 int /*<<< orphan*/  stub6 () ; 
 int /*<<< orphan*/  stub7 (char) ; 
 int /*<<< orphan*/  stub8 () ; 

__attribute__((used)) static void put_packet(char *buffer)
{
	unsigned char checksum;
	int count;
	char ch;

	/*
	 * $<packet info>#<checksum>.
	 */
	while (1) {
		dbg_io_ops->write_char('$');
		checksum = 0;
		count = 0;

		while ((ch = buffer[count])) {
			dbg_io_ops->write_char(ch);
			checksum += ch;
			count++;
		}

		dbg_io_ops->write_char('#');
		dbg_io_ops->write_char(hex_asc_hi(checksum));
		dbg_io_ops->write_char(hex_asc_lo(checksum));
		if (dbg_io_ops->flush)
			dbg_io_ops->flush();

		/* Now see what we get in reply. */
		ch = gdbstub_read_wait();

		if (ch == 3)
			ch = gdbstub_read_wait();

		/* If we get an ACK, we are done. */
		if (ch == '+')
			return;

		/*
		 * If we get the start of another packet, this means
		 * that GDB is attempting to reconnect.  We will NAK
		 * the packet being sent, and stop trying to send this
		 * packet.
		 */
		if (ch == '$') {
			dbg_io_ops->write_char('-');
			if (dbg_io_ops->flush)
				dbg_io_ops->flush();
			return;
		}
	}
}