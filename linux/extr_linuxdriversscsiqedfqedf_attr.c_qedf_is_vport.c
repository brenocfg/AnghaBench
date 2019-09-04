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
struct qedf_ctx {TYPE_1__* lport; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vport; } ;

/* Variables and functions */

inline bool qedf_is_vport(struct qedf_ctx *qedf)
{
	return qedf->lport->vport != NULL;
}