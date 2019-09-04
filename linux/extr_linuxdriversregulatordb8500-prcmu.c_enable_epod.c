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
typedef  size_t u16 ;

/* Variables and functions */
 int /*<<< orphan*/  EPOD_STATE_ON ; 
 int /*<<< orphan*/  EPOD_STATE_RAMRET ; 
 int* epod_on ; 
 int* epod_ramret ; 
 int prcmu_set_epod (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enable_epod(u16 epod_id, bool ramret)
{
	int ret;

	if (ramret) {
		if (!epod_on[epod_id]) {
			ret = prcmu_set_epod(epod_id, EPOD_STATE_RAMRET);
			if (ret < 0)
				return ret;
		}
		epod_ramret[epod_id] = true;
	} else {
		ret = prcmu_set_epod(epod_id, EPOD_STATE_ON);
		if (ret < 0)
			return ret;
		epod_on[epod_id] = true;
	}

	return 0;
}