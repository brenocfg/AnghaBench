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
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_NONE ; 
#define  READ_BUFFER 129 
#define  TEST_UNIT_READY 128 
 int spi_execute (struct scsi_device*,char const*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spi_dv_device_get_echo_buffer(struct scsi_device *sdev, u8 *buffer)
{
	int l, result;

	/* first off do a test unit ready.  This can error out 
	 * because of reservations or some other reason.  If it
	 * fails, the device won't let us write to the echo buffer
	 * so just return failure */
	
	static const char spi_test_unit_ready[] = {
		TEST_UNIT_READY, 0, 0, 0, 0, 0
	};

	static const char spi_read_buffer_descriptor[] = {
		READ_BUFFER, 0x0b, 0, 0, 0, 0, 0, 0, 4, 0
	};

	
	/* We send a set of three TURs to clear any outstanding 
	 * unit attention conditions if they exist (Otherwise the
	 * buffer tests won't be happy).  If the TUR still fails
	 * (reservation conflict, device not ready, etc) just
	 * skip the write tests */
	for (l = 0; ; l++) {
		result = spi_execute(sdev, spi_test_unit_ready, DMA_NONE, 
				     NULL, 0, NULL);

		if(result) {
			if(l >= 3)
				return 0;
		} else {
			/* TUR succeeded */
			break;
		}
	}

	result = spi_execute(sdev, spi_read_buffer_descriptor, 
			     DMA_FROM_DEVICE, buffer, 4, NULL);

	if (result)
		/* Device has no echo buffer */
		return 0;

	return buffer[3] + ((buffer[2] & 0x1f) << 8);
}