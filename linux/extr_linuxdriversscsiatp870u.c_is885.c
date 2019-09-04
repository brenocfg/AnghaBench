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
struct atp_unit {TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ ATP885_DEVID ; 

__attribute__((used)) static inline bool is885(struct atp_unit *atp)
{
	return atp->pdev->device == ATP885_DEVID;
}