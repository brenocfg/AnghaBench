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
struct subchannel_id {int /*<<< orphan*/  ssid; int /*<<< orphan*/  sch_no; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int length; int code; } ;
struct chsc_ssqd_area {TYPE_1__ response; int /*<<< orphan*/  ssid; int /*<<< orphan*/  last_sch; int /*<<< orphan*/  first_sch; TYPE_2__ request; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ chsc (struct chsc_ssqd_area*) ; 
 int chsc_error_from_response (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct chsc_ssqd_area*,int /*<<< orphan*/ ,int) ; 

int chsc_ssqd(struct subchannel_id schid, struct chsc_ssqd_area *ssqd)
{
	memset(ssqd, 0, sizeof(*ssqd));
	ssqd->request.length = 0x0010;
	ssqd->request.code = 0x0024;
	ssqd->first_sch = schid.sch_no;
	ssqd->last_sch = schid.sch_no;
	ssqd->ssid = schid.ssid;

	if (chsc(ssqd))
		return -EIO;

	return chsc_error_from_response(ssqd->response.code);
}