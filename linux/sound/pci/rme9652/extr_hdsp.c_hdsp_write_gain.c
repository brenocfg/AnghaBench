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
struct hdsp {scalar_t__ io_type; unsigned short* mixer_matrix; } ;

/* Variables and functions */
 scalar_t__ H9632 ; 
 scalar_t__ H9652 ; 
 int /*<<< orphan*/  HDSP_LONG_WAIT ; 
 unsigned int HDSP_MATRIX_MIXER_SIZE ; 
 int HDSP_fifoData ; 
 scalar_t__ hdsp_fifo_wait (struct hdsp*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int,unsigned int) ; 

__attribute__((used)) static int hdsp_write_gain(struct hdsp *hdsp, unsigned int addr, unsigned short data)
{
	unsigned int ad;

	if (addr >= HDSP_MATRIX_MIXER_SIZE)
		return -1;

	if (hdsp->io_type == H9652 || hdsp->io_type == H9632) {

		/* from martin bjornsen:

		   "You can only write dwords to the
		   mixer memory which contain two
		   mixer values in the low and high
		   word. So if you want to change
		   value 0 you have to read value 1
		   from the cache and write both to
		   the first dword in the mixer
		   memory."
		*/

		if (hdsp->io_type == H9632 && addr >= 512)
			return 0;

		if (hdsp->io_type == H9652 && addr >= 1352)
			return 0;

		hdsp->mixer_matrix[addr] = data;


		/* `addr' addresses a 16-bit wide address, but
		   the address space accessed via hdsp_write
		   uses byte offsets. put another way, addr
		   varies from 0 to 1351, but to access the
		   corresponding memory location, we need
		   to access 0 to 2703 ...
		*/
		ad = addr/2;

		hdsp_write (hdsp, 4096 + (ad*4),
			    (hdsp->mixer_matrix[(addr&0x7fe)+1] << 16) +
			    hdsp->mixer_matrix[addr&0x7fe]);

		return 0;

	} else {

		ad = (addr << 16) + data;

		if (hdsp_fifo_wait(hdsp, 127, HDSP_LONG_WAIT))
			return -1;

		hdsp_write (hdsp, HDSP_fifoData, ad);
		hdsp->mixer_matrix[addr] = data;

	}

	return 0;
}