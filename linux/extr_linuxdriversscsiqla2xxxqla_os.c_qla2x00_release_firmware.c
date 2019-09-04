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
struct TYPE_2__ {int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int FW_BLOBS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* qla_fw_blobs ; 
 int /*<<< orphan*/  qla_fw_lock ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla2x00_release_firmware(void)
{
	int idx;

	mutex_lock(&qla_fw_lock);
	for (idx = 0; idx < FW_BLOBS; idx++)
		release_firmware(qla_fw_blobs[idx].fw);
	mutex_unlock(&qla_fw_lock);
}