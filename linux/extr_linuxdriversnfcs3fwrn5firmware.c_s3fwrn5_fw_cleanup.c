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
struct s3fwrn5_fw_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s3fwrn5_fw_release_firmware (struct s3fwrn5_fw_info*) ; 

void s3fwrn5_fw_cleanup(struct s3fwrn5_fw_info *fw_info)
{
	s3fwrn5_fw_release_firmware(fw_info);
}