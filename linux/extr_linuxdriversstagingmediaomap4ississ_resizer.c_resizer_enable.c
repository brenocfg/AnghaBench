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
struct iss_resizer_device {int dummy; } ;
struct iss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_RESIZER ; 
 int /*<<< orphan*/  RSZ_EN_EN ; 
 int /*<<< orphan*/  RSZ_SRC_EN ; 
 int /*<<< orphan*/  RSZ_SRC_EN_SRC_EN ; 
 int /*<<< orphan*/  RZA_EN ; 
 int /*<<< orphan*/  iss_reg_update (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iss_device* to_iss_device (struct iss_resizer_device*) ; 

__attribute__((used)) static void resizer_enable(struct iss_resizer_device *resizer, u8 enable)
{
	struct iss_device *iss = to_iss_device(resizer);

	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_EN,
		       RSZ_SRC_EN_SRC_EN, enable ? RSZ_SRC_EN_SRC_EN : 0);

	/* TODO: Enable RSZB */
	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_EN, RSZ_EN_EN,
		       enable ? RSZ_EN_EN : 0);
}