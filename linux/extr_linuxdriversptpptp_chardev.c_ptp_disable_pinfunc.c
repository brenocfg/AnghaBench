#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int index; } ;
struct TYPE_4__ {unsigned int index; } ;
struct ptp_clock_request {TYPE_1__ perout; int /*<<< orphan*/  type; TYPE_2__ extts; } ;
struct ptp_clock_info {int (* enable ) (struct ptp_clock_info*,struct ptp_clock_request*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  rq ;
typedef  enum ptp_pin_function { ____Placeholder_ptp_pin_function } ptp_pin_function ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PTP_CLK_REQ_EXTTS ; 
 int /*<<< orphan*/  PTP_CLK_REQ_PEROUT ; 
#define  PTP_PF_EXTTS 131 
#define  PTP_PF_NONE 130 
#define  PTP_PF_PEROUT 129 
#define  PTP_PF_PHYSYNC 128 
 int /*<<< orphan*/  memset (struct ptp_clock_request*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ptp_clock_info*,struct ptp_clock_request*,int /*<<< orphan*/ ) ; 
 int stub2 (struct ptp_clock_info*,struct ptp_clock_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ptp_disable_pinfunc(struct ptp_clock_info *ops,
			       enum ptp_pin_function func, unsigned int chan)
{
	struct ptp_clock_request rq;
	int err = 0;

	memset(&rq, 0, sizeof(rq));

	switch (func) {
	case PTP_PF_NONE:
		break;
	case PTP_PF_EXTTS:
		rq.type = PTP_CLK_REQ_EXTTS;
		rq.extts.index = chan;
		err = ops->enable(ops, &rq, 0);
		break;
	case PTP_PF_PEROUT:
		rq.type = PTP_CLK_REQ_PEROUT;
		rq.perout.index = chan;
		err = ops->enable(ops, &rq, 0);
		break;
	case PTP_PF_PHYSYNC:
		break;
	default:
		return -EINVAL;
	}

	return err;
}