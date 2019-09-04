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
typedef  int u32 ;
struct soc_sensor_entry {scalar_t__ locked; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  MBI_REG_WRITE ; 
 int QRK_DTS_MASK_TP_THRES ; 
 int /*<<< orphan*/  QRK_DTS_REG_OFFSET_PTPS ; 
 int QRK_DTS_SAFE_TP_THRES ; 
 int QRK_DTS_SHIFT_TP ; 
 int QRK_DTS_TEMP_BASE ; 
 int /*<<< orphan*/  QRK_MBI_UNIT_RMU ; 
 int /*<<< orphan*/  dts_update_mutex ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_trip_temp(struct soc_sensor_entry *aux_entry,
				int trip, int temp)
{
	u32 out;
	u32 temp_out;
	u32 store_ptps;
	int ret;

	mutex_lock(&dts_update_mutex);
	if (aux_entry->locked) {
		ret = -EPERM;
		goto failed;
	}

	ret = iosf_mbi_read(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			    QRK_DTS_REG_OFFSET_PTPS, &store_ptps);
	if (ret)
		goto failed;

	/*
	 * Protection against unsafe trip point thresdhold value.
	 * As Quark X1000 data-sheet does not provide any recommendation
	 * regarding the safe trip point threshold value to use, we choose
	 * the safe value according to the threshold value set by UEFI BIOS.
	 */
	if (temp > QRK_DTS_SAFE_TP_THRES)
		temp = QRK_DTS_SAFE_TP_THRES;

	/*
	 * Thermal Sensor Programmable Trip Point Register has 8-bit
	 * fields for critical (catastrophic) and hot set trip point
	 * thresholds. The threshold value is always offset by its
	 * temperature base (50 degree Celsius).
	 */
	temp_out = temp + QRK_DTS_TEMP_BASE;
	out = (store_ptps & ~(QRK_DTS_MASK_TP_THRES <<
		(trip * QRK_DTS_SHIFT_TP)));
	out |= (temp_out & QRK_DTS_MASK_TP_THRES) <<
		(trip * QRK_DTS_SHIFT_TP);

	ret = iosf_mbi_write(QRK_MBI_UNIT_RMU, MBI_REG_WRITE,
			     QRK_DTS_REG_OFFSET_PTPS, out);

failed:
	mutex_unlock(&dts_update_mutex);
	return ret;
}