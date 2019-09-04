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
typedef  scalar_t__ u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_MODE_SCSI_MSK ; 
 scalar_t__ SCB_DISCONNECTED_LISTS ; 
 int TCL_LUN (scalar_t__) ; 
 int TCL_TARGET_OFFSET (scalar_t__) ; 
 scalar_t__ ahd_get_scbptr (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_scbptr (struct ahd_softc*,int) ; 

__attribute__((used)) static inline u_int
ahd_index_busy_tcl(struct ahd_softc *ahd, u_int *saved_scbid, u_int tcl)
{
	/*
	 * Index to the SCB that contains the busy entry.
	 */
	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	*saved_scbid = ahd_get_scbptr(ahd);
	ahd_set_scbptr(ahd, TCL_LUN(tcl)
		     | ((TCL_TARGET_OFFSET(tcl) & 0xC) << 4));

	/*
	 * And now calculate the SCB offset to the entry.
	 * Each entry is 2 bytes wide, hence the
	 * multiplication by 2.
	 */
	return (((TCL_TARGET_OFFSET(tcl) & 0x3) << 1) + SCB_DISCONNECTED_LISTS);
}