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
typedef  int u8 ;
typedef  int u16 ;
struct w1_slave {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 size_t W1_F19_WRITE_DATA_LIMIT ; 
 int W1_F19_WRITE_DATA_NO_STOP ; 
 int W1_F19_WRITE_DATA_ONLY ; 
 int W1_F19_WRITE_DATA_ONLY_WITH_STOP ; 
 int W1_F19_WRITE_DATA_WITH_STOP ; 
 int __w1_f19_i2c_write (struct w1_slave*,int*,int,int const*,int) ; 
 scalar_t__ w1_reset_resume_command (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w1_f19_i2c_write(struct w1_slave *sl, u16 i2c_address,
	const u8 *buffer, size_t count, bool stop)
{
	int result;
	int remaining = count;
	const u8 *p;
	u8 command[2];

	/* Check input. */
	if (count == 0)
		return -EOPNOTSUPP;

	/* Check whether we need multiple commands. */
	if (count <= W1_F19_WRITE_DATA_LIMIT) {
		/*
		 * Small data amount. Data can be sent with
		 * a single onewire command.
		 */

		/* Send all data to DS28E17. */
		command[0] = (stop ? W1_F19_WRITE_DATA_WITH_STOP
			: W1_F19_WRITE_DATA_NO_STOP);
		command[1] = i2c_address << 1;
		result = __w1_f19_i2c_write(sl, command, 2, buffer, count);
	} else {
		/* Large data amount. Data has to be sent in multiple chunks. */

		/* Send first chunk to DS28E17. */
		p = buffer;
		command[0] = W1_F19_WRITE_DATA_NO_STOP;
		command[1] = i2c_address << 1;
		result = __w1_f19_i2c_write(sl, command, 2, p,
			W1_F19_WRITE_DATA_LIMIT);
		if (result < 0)
			return result;

		/* Resume to same DS28E17. */
		if (w1_reset_resume_command(sl->master))
			return -EIO;

		/* Next data chunk. */
		p += W1_F19_WRITE_DATA_LIMIT;
		remaining -= W1_F19_WRITE_DATA_LIMIT;

		while (remaining > W1_F19_WRITE_DATA_LIMIT) {
			/* Send intermediate chunk to DS28E17. */
			command[0] = W1_F19_WRITE_DATA_ONLY;
			result = __w1_f19_i2c_write(sl, command, 1, p,
					W1_F19_WRITE_DATA_LIMIT);
			if (result < 0)
				return result;

			/* Resume to same DS28E17. */
			if (w1_reset_resume_command(sl->master))
				return -EIO;

			/* Next data chunk. */
			p += W1_F19_WRITE_DATA_LIMIT;
			remaining -= W1_F19_WRITE_DATA_LIMIT;
		}

		/* Send final chunk to DS28E17. */
		command[0] = (stop ? W1_F19_WRITE_DATA_ONLY_WITH_STOP
			: W1_F19_WRITE_DATA_ONLY);
		result = __w1_f19_i2c_write(sl, command, 1, p, remaining);
	}

	return result;
}