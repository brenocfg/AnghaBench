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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_MODE_SCSI_MSK ; 
 int EINVAL ; 
 int /*<<< orphan*/  SEEADR ; 
 int /*<<< orphan*/  SEECTL ; 
 scalar_t__ SEEDAT ; 
 scalar_t__ SEEOP_READ ; 
 scalar_t__ SEESTART ; 
 void* ahd_inb (struct ahd_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ahd_inw (struct ahd_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ahd_wait_seeprom (struct ahd_softc*) ; 

int
ahd_read_seeprom(struct ahd_softc *ahd, uint16_t *buf,
		 u_int start_addr, u_int count, int bytestream)
{
	u_int cur_addr;
	u_int end_addr;
	int   error;

	/*
	 * If we never make it through the loop even once,
	 * we were passed invalid arguments.
	 */
	error = EINVAL;
	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	end_addr = start_addr + count;
	for (cur_addr = start_addr; cur_addr < end_addr; cur_addr++) {

		ahd_outb(ahd, SEEADR, cur_addr);
		ahd_outb(ahd, SEECTL, SEEOP_READ | SEESTART);
		
		error = ahd_wait_seeprom(ahd);
		if (error)
			break;
		if (bytestream != 0) {
			uint8_t *bytestream_ptr;

			bytestream_ptr = (uint8_t *)buf;
			*bytestream_ptr++ = ahd_inb(ahd, SEEDAT);
			*bytestream_ptr = ahd_inb(ahd, SEEDAT+1);
		} else {
			/*
			 * ahd_inw() already handles machine byte order.
			 */
			*buf = ahd_inw(ahd, SEEDAT);
		}
		buf++;
	}
	return (error);
}