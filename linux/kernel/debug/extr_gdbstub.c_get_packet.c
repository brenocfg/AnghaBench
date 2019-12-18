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
 int BUFMAX ; 
 TYPE_1__* dbg_io_ops ; 
 char gdbstub_read_wait () ; 
 unsigned char hex_to_bin (char) ; 
 int kgdb_connected ; 
 int /*<<< orphan*/  stub1 (char) ; 
 int /*<<< orphan*/  stub2 (char) ; 
 int /*<<< orphan*/  stub3 () ; 

__attribute__((used)) static void get_packet(char *buffer)
{
	unsigned char checksum;
	unsigned char xmitcsum;
	int count;
	char ch;

	do {
		/*
		 * Spin and wait around for the start character, ignore all
		 * other characters:
		 */
		while ((ch = (gdbstub_read_wait())) != '$')
			/* nothing */;

		kgdb_connected = 1;
		checksum = 0;
		xmitcsum = -1;

		count = 0;

		/*
		 * now, read until a # or end of buffer is found:
		 */
		while (count < (BUFMAX - 1)) {
			ch = gdbstub_read_wait();
			if (ch == '#')
				break;
			checksum = checksum + ch;
			buffer[count] = ch;
			count = count + 1;
		}

		if (ch == '#') {
			xmitcsum = hex_to_bin(gdbstub_read_wait()) << 4;
			xmitcsum += hex_to_bin(gdbstub_read_wait());

			if (checksum != xmitcsum)
				/* failed checksum */
				dbg_io_ops->write_char('-');
			else
				/* successful transfer */
				dbg_io_ops->write_char('+');
			if (dbg_io_ops->flush)
				dbg_io_ops->flush();
		}
		buffer[count] = 0;
	} while (checksum != xmitcsum);
}