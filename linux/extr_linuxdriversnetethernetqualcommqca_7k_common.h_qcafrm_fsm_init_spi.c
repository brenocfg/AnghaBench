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
struct qcafrm_handle {int /*<<< orphan*/  init; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCAFRM_HW_LEN0 ; 

__attribute__((used)) static inline void qcafrm_fsm_init_spi(struct qcafrm_handle *handle)
{
	handle->init = QCAFRM_HW_LEN0;
	handle->state = handle->init;
}