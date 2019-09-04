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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int (* update_bits ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct qcom_smem_state {int /*<<< orphan*/  priv; TYPE_1__ ops; scalar_t__ orphan; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int ENXIO ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qcom_smem_state_update_bits(struct qcom_smem_state *state,
				u32 mask,
				u32 value)
{
	if (state->orphan)
		return -ENXIO;

	if (!state->ops.update_bits)
		return -ENOTSUPP;

	return state->ops.update_bits(state->priv, mask, value);
}