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
struct iss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKCTRL ; 
 int /*<<< orphan*/  CLKSTAT ; 
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  HL_IRQENABLE_CLR (int) ; 
 int /*<<< orphan*/  HL_IRQENABLE_SET (int) ; 
 int /*<<< orphan*/  HL_IRQSTATUS (int) ; 
 int /*<<< orphan*/  HL_REVISION ; 
 int /*<<< orphan*/  HL_SYSCONFIG ; 
 int /*<<< orphan*/  ISS_PRINT_REGISTER (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void iss_print_status(struct iss_device *iss)
{
	dev_dbg(iss->dev, "-------------ISS HL Register dump-------------\n");

	ISS_PRINT_REGISTER(iss, HL_REVISION);
	ISS_PRINT_REGISTER(iss, HL_SYSCONFIG);
	ISS_PRINT_REGISTER(iss, HL_IRQSTATUS(5));
	ISS_PRINT_REGISTER(iss, HL_IRQENABLE_SET(5));
	ISS_PRINT_REGISTER(iss, HL_IRQENABLE_CLR(5));
	ISS_PRINT_REGISTER(iss, CTRL);
	ISS_PRINT_REGISTER(iss, CLKCTRL);
	ISS_PRINT_REGISTER(iss, CLKSTAT);

	dev_dbg(iss->dev, "-----------------------------------------------\n");
}