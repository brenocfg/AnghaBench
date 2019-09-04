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
struct iss_device {int /*<<< orphan*/  crashed; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ISS_HL_SYSCONFIG ; 
 int ISS_HL_SYSCONFIG_SOFTRESET ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_TOP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int iss_poll_condition_timeout (int,int,int,int) ; 
 int iss_reg_read (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_set (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  media_entity_enum_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iss_reset(struct iss_device *iss)
{
	unsigned int timeout;

	iss_reg_set(iss, OMAP4_ISS_MEM_TOP, ISS_HL_SYSCONFIG,
		    ISS_HL_SYSCONFIG_SOFTRESET);

	timeout = iss_poll_condition_timeout(
		!(iss_reg_read(iss, OMAP4_ISS_MEM_TOP, ISS_HL_SYSCONFIG) &
		ISS_HL_SYSCONFIG_SOFTRESET), 1000, 10, 100);
	if (timeout) {
		dev_err(iss->dev, "ISS reset timeout\n");
		return -ETIMEDOUT;
	}

	media_entity_enum_zero(&iss->crashed);

	return 0;
}