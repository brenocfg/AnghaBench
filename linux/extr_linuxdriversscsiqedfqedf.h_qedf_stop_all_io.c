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
struct qedf_ctx {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_DBG_STOP_IO ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void qedf_stop_all_io(struct qedf_ctx *qedf)
{
	set_bit(QEDF_DBG_STOP_IO, &qedf->flags);
}