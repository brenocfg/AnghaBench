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
struct ssusb_mtk {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssusb_host_cleanup (struct ssusb_mtk*) ; 

void ssusb_host_exit(struct ssusb_mtk *ssusb)
{
	of_platform_depopulate(ssusb->dev);
	ssusb_host_cleanup(ssusb);
}