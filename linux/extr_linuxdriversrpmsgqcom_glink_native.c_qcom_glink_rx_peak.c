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
struct qcom_glink {TYPE_1__* rx_pipe; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* peak ) (TYPE_1__*,void*,unsigned int,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*,unsigned int,size_t) ; 

__attribute__((used)) static void qcom_glink_rx_peak(struct qcom_glink *glink,
			       void *data, unsigned int offset, size_t count)
{
	glink->rx_pipe->peak(glink->rx_pipe, data, offset, count);
}