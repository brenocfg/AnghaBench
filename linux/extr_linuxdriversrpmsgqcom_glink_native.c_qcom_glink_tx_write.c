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
struct qcom_glink {TYPE_1__* tx_pipe; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (TYPE_1__*,void const*,size_t,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,void const*,size_t,void const*,size_t) ; 

__attribute__((used)) static void qcom_glink_tx_write(struct qcom_glink *glink,
				const void *hdr, size_t hlen,
				const void *data, size_t dlen)
{
	glink->tx_pipe->write(glink->tx_pipe, hdr, hlen, data, dlen);
}