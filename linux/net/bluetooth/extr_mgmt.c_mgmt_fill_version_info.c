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
struct mgmt_rp_read_version {int /*<<< orphan*/  revision; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_REVISION ; 
 int /*<<< orphan*/  MGMT_VERSION ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

void mgmt_fill_version_info(void *ver)
{
	struct mgmt_rp_read_version *rp = ver;

	rp->version = MGMT_VERSION;
	rp->revision = cpu_to_le16(MGMT_REVISION);
}