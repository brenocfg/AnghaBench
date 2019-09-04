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
typedef  int /*<<< orphan*/  u64 ;
struct tc_service_curve {int dummy; } ;
struct hfsc_class {int /*<<< orphan*/  cl_flags; int /*<<< orphan*/  cl_total; int /*<<< orphan*/  cl_usc; int /*<<< orphan*/  cl_ulimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFSC_USC ; 
 int /*<<< orphan*/  rtsc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc2isc (struct tc_service_curve*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hfsc_change_usc(struct hfsc_class *cl, struct tc_service_curve *usc,
		u64 cur_time)
{
	sc2isc(usc, &cl->cl_usc);
	rtsc_init(&cl->cl_ulimit, &cl->cl_usc, cur_time, cl->cl_total);
	cl->cl_flags |= HFSC_USC;
}