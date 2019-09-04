#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_8__ {scalar_t__ output; } ;
struct TYPE_7__ {scalar_t__ output; } ;
struct TYPE_6__ {scalar_t__ input; } ;
struct vpfe_resizer_device {int /*<<< orphan*/  base_addr; TYPE_4__ resizer_b; TYPE_3__ resizer_a; TYPE_2__ crop_resizer; } ;
struct TYPE_5__ {scalar_t__ input; } ;
struct vpfe_device {TYPE_1__ vpfe_ipipeif; } ;

/* Variables and functions */
 scalar_t__ IPIPEIF_INPUT_MEMORY ; 
 scalar_t__ RESIZER_CROP_INPUT_IPIPEIF ; 
 scalar_t__ RESIZER_CROP_INPUT_NONE ; 
 scalar_t__ RESIZER_OUTPUT_NONE ; 
 int /*<<< orphan*/  RSZ_A ; 
 int /*<<< orphan*/  RSZ_B ; 
 int /*<<< orphan*/  RSZ_SRC_EN ; 
 unsigned char regr_rsz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsz_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_resizer_device*) ; 

__attribute__((used)) static void resizer_enable(struct vpfe_resizer_device *resizer, int en)
{
	struct vpfe_device *vpfe_dev = to_vpfe_device(resizer);
	u16 ipipeif_sink = vpfe_dev->vpfe_ipipeif.input;
	unsigned char val;

	if (resizer->crop_resizer.input == RESIZER_CROP_INPUT_NONE)
		return;

	if (resizer->crop_resizer.input == RESIZER_CROP_INPUT_IPIPEIF &&
	   ipipeif_sink == IPIPEIF_INPUT_MEMORY) {
		do {
			val = regr_rsz(resizer->base_addr, RSZ_SRC_EN);
		} while (val);

		if (resizer->resizer_a.output != RESIZER_OUTPUT_NONE) {
			do {
				val = regr_rsz(resizer->base_addr, RSZ_A);
			} while (val);
		}
		if (resizer->resizer_b.output != RESIZER_OUTPUT_NONE) {
			do {
				val = regr_rsz(resizer->base_addr, RSZ_B);
			} while (val);
		}
	}
	if (resizer->resizer_a.output != RESIZER_OUTPUT_NONE)
		rsz_enable(resizer->base_addr, RSZ_A, en);

	if (resizer->resizer_b.output != RESIZER_OUTPUT_NONE)
		rsz_enable(resizer->base_addr, RSZ_B, en);
}