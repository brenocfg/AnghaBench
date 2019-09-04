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

/* Variables and functions */
 int /*<<< orphan*/  base_cb_idx ; 
 int /*<<< orphan*/  config_cb_idx ; 
 int /*<<< orphan*/  ctl_cb_idx ; 
 int hbas_to_enumerate ; 
 int /*<<< orphan*/  mpt2sas_raid_template ; 
 int /*<<< orphan*/  mpt3sas_base_release_callback_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt3sas_raid_template ; 
 int /*<<< orphan*/  mpt3sas_transport_template ; 
 int /*<<< orphan*/  port_enable_cb_idx ; 
 int /*<<< orphan*/  raid_class_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_release_transport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_io_cb_idx ; 
 int /*<<< orphan*/  scsih_cb_idx ; 
 int /*<<< orphan*/  tm_cb_idx ; 
 int /*<<< orphan*/  tm_sas_control_cb_idx ; 
 int /*<<< orphan*/  tm_tr_cb_idx ; 
 int /*<<< orphan*/  tm_tr_volume_cb_idx ; 
 int /*<<< orphan*/  transport_cb_idx ; 

__attribute__((used)) static void
scsih_exit(void)
{

	mpt3sas_base_release_callback_handler(scsi_io_cb_idx);
	mpt3sas_base_release_callback_handler(tm_cb_idx);
	mpt3sas_base_release_callback_handler(base_cb_idx);
	mpt3sas_base_release_callback_handler(port_enable_cb_idx);
	mpt3sas_base_release_callback_handler(transport_cb_idx);
	mpt3sas_base_release_callback_handler(scsih_cb_idx);
	mpt3sas_base_release_callback_handler(config_cb_idx);
	mpt3sas_base_release_callback_handler(ctl_cb_idx);

	mpt3sas_base_release_callback_handler(tm_tr_cb_idx);
	mpt3sas_base_release_callback_handler(tm_tr_volume_cb_idx);
	mpt3sas_base_release_callback_handler(tm_sas_control_cb_idx);

/* raid transport support */
	if (hbas_to_enumerate != 1)
		raid_class_release(mpt3sas_raid_template);
	if (hbas_to_enumerate != 2)
		raid_class_release(mpt2sas_raid_template);
	sas_release_transport(mpt3sas_transport_template);
}