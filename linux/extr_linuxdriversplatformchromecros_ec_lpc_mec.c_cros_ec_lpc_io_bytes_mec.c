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
typedef  scalar_t__ u8 ;
typedef  enum cros_ec_lpc_mec_io_type { ____Placeholder_cros_ec_lpc_mec_io_type } cros_ec_lpc_mec_io_type ;
typedef  enum cros_ec_lpc_mec_emi_access_mode { ____Placeholder_cros_ec_lpc_mec_emi_access_mode } cros_ec_lpc_mec_emi_access_mode ;

/* Variables and functions */
 int ACCESS_TYPE_BYTE ; 
 int ACCESS_TYPE_LONG_AUTO_INCREMENT ; 
 unsigned int MEC_EMI_EC_DATA_B0 ; 
 int MEC_EMI_EC_DATA_B3 ; 
 int MEC_IO_READ ; 
 int MEC_IO_WRITE ; 
 int /*<<< orphan*/  cros_ec_lpc_mec_emi_write_address (unsigned int,int) ; 
 scalar_t__ inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 

u8 cros_ec_lpc_io_bytes_mec(enum cros_ec_lpc_mec_io_type io_type,
			    unsigned int offset, unsigned int length,
			    u8 *buf)
{
	int i = 0;
	int io_addr;
	u8 sum = 0;
	enum cros_ec_lpc_mec_emi_access_mode access, new_access;

	/*
	 * Long access cannot be used on misaligned data since reading B0 loads
	 * the data register and writing B3 flushes.
	 */
	if (offset & 0x3 || length < 4)
		access = ACCESS_TYPE_BYTE;
	else
		access = ACCESS_TYPE_LONG_AUTO_INCREMENT;

	mutex_lock(&io_mutex);

	/* Initialize I/O at desired address */
	cros_ec_lpc_mec_emi_write_address(offset, access);

	/* Skip bytes in case of misaligned offset */
	io_addr = MEC_EMI_EC_DATA_B0 + (offset & 0x3);
	while (i < length) {
		while (io_addr <= MEC_EMI_EC_DATA_B3) {
			if (io_type == MEC_IO_READ)
				buf[i] = inb(io_addr++);
			else
				outb(buf[i], io_addr++);

			sum += buf[i++];
			offset++;

			/* Extra bounds check in case of misaligned length */
			if (i == length)
				goto done;
		}

		/*
		 * Use long auto-increment access except for misaligned write,
		 * since writing B3 triggers the flush.
		 */
		if (length - i < 4 && io_type == MEC_IO_WRITE)
			new_access = ACCESS_TYPE_BYTE;
		else
			new_access = ACCESS_TYPE_LONG_AUTO_INCREMENT;

		if (new_access != access ||
		    access != ACCESS_TYPE_LONG_AUTO_INCREMENT) {
			access = new_access;
			cros_ec_lpc_mec_emi_write_address(offset, access);
		}

		/* Access [B0, B3] on each loop pass */
		io_addr = MEC_EMI_EC_DATA_B0;
	}

done:
	mutex_unlock(&io_mutex);

	return sum;
}