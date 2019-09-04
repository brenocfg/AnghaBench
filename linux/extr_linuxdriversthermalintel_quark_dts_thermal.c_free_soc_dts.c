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
struct soc_sensor_entry {int /*<<< orphan*/  tzone; int /*<<< orphan*/  store_ptps; int /*<<< orphan*/  store_dts_enable; int /*<<< orphan*/  locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBI_REG_WRITE ; 
 int /*<<< orphan*/  QRK_DTS_REG_OFFSET_ENABLE ; 
 int /*<<< orphan*/  QRK_DTS_REG_OFFSET_PTPS ; 
 int /*<<< orphan*/  QRK_MBI_UNIT_RMU ; 
 int /*<<< orphan*/  dts_update_mutex ; 
 int /*<<< orphan*/  iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct soc_sensor_entry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_soc_dts(struct soc_sensor_entry *aux_entry)
{
	if (aux_entry) {
		if (!aux_entry->locked) {
			mutex_lock(&dts_update_mutex);
			iosf_mbi_write(QRK_MBI_UNIT_RMU, MBI_REG_WRITE,
				       QRK_DTS_REG_OFFSET_ENABLE,
				       aux_entry->store_dts_enable);

			iosf_mbi_write(QRK_MBI_UNIT_RMU, MBI_REG_WRITE,
				       QRK_DTS_REG_OFFSET_PTPS,
				       aux_entry->store_ptps);
			mutex_unlock(&dts_update_mutex);
		}
		thermal_zone_device_unregister(aux_entry->tzone);
		kfree(aux_entry);
	}
}