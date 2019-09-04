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
struct msr_hwp_request {scalar_t__ hwp_min; scalar_t__ hwp_max; scalar_t__ hwp_desired; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,int,scalar_t__,scalar_t__) ; 

int verify_hwp_req_self_consistency(int cpu, struct msr_hwp_request *req)
{
	/* fail if min > max requested */
	if (req->hwp_min > req->hwp_max) {
		errx(1, "cpu%d: requested hwp-min %d > hwp_max %d",
			cpu, req->hwp_min, req->hwp_max);
	}

	/* fail if desired > max requestd */
	if (req->hwp_desired && (req->hwp_desired > req->hwp_max)) {
		errx(1, "cpu%d: requested hwp-desired %d > hwp_max %d",
			cpu, req->hwp_desired, req->hwp_max);
	}
	/* fail if desired < min requestd */
	if (req->hwp_desired && (req->hwp_desired < req->hwp_min)) {
		errx(1, "cpu%d: requested hwp-desired %d < requested hwp_min %d",
			cpu, req->hwp_desired, req->hwp_min);
	}

	return 0;
}