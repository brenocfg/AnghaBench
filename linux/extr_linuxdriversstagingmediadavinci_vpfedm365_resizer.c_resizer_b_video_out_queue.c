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
struct vpfe_resizer_device {int /*<<< orphan*/  config; int /*<<< orphan*/  base_addr; } ;
struct vpfe_device {struct vpfe_resizer_device vpfe_resizer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSZ_B ; 
 int resizer_set_outaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int resizer_b_video_out_queue(struct vpfe_device *vpfe_dev,
				     unsigned long addr)
{
	struct vpfe_resizer_device *resizer = &vpfe_dev->vpfe_resizer;

	return resizer_set_outaddr(resizer->base_addr,
				   &resizer->config, RSZ_B, addr);
}