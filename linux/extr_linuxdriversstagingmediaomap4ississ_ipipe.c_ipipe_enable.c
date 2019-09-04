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
typedef  scalar_t__ u8 ;
struct iss_ipipe_device {int dummy; } ;
struct iss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPIPE_SRC_EN ; 
 int /*<<< orphan*/  IPIPE_SRC_EN_EN ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_IPIPE ; 
 int /*<<< orphan*/  iss_reg_update (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iss_device* to_iss_device (struct iss_ipipe_device*) ; 

__attribute__((used)) static void ipipe_enable(struct iss_ipipe_device *ipipe, u8 enable)
{
	struct iss_device *iss = to_iss_device(ipipe);

	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_SRC_EN,
		       IPIPE_SRC_EN_EN, enable ? IPIPE_SRC_EN_EN : 0);
}