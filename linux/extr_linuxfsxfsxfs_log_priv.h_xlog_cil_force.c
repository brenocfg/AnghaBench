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
struct xlog {TYPE_1__* l_cilp; } ;
struct TYPE_2__ {int /*<<< orphan*/  xc_current_sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  xlog_cil_force_lsn (struct xlog*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
xlog_cil_force(struct xlog *log)
{
	xlog_cil_force_lsn(log, log->l_cilp->xc_current_sequence);
}