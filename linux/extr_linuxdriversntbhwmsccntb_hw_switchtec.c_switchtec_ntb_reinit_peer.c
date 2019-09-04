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
struct switchtec_ntb {TYPE_1__* stdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  switchtec_ntb_deinit_shared_mw (struct switchtec_ntb*) ; 
 int /*<<< orphan*/  switchtec_ntb_init_mw (struct switchtec_ntb*) ; 
 int switchtec_ntb_init_shared_mw (struct switchtec_ntb*) ; 

__attribute__((used)) static int switchtec_ntb_reinit_peer(struct switchtec_ntb *sndev)
{
	dev_info(&sndev->stdev->dev, "peer reinitialized\n");
	switchtec_ntb_deinit_shared_mw(sndev);
	switchtec_ntb_init_mw(sndev);
	return switchtec_ntb_init_shared_mw(sndev);
}