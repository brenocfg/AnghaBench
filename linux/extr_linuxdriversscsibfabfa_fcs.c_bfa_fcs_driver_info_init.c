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
struct bfa_fcs_driver_info_s {int dummy; } ;
struct bfa_fcs_s {int /*<<< orphan*/  fabric; struct bfa_fcs_driver_info_s driver_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcs_fabric_nsymb_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_psymb_init (int /*<<< orphan*/ *) ; 

void
bfa_fcs_driver_info_init(struct bfa_fcs_s *fcs,
			struct bfa_fcs_driver_info_s *driver_info)
{

	fcs->driver_info = *driver_info;

	bfa_fcs_fabric_psymb_init(&fcs->fabric);
	bfa_fcs_fabric_nsymb_init(&fcs->fabric);
}