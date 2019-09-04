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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct ahd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  role_t ;

/* Variables and functions */

int
ahd_platform_abort_scbs(struct ahd_softc *ahd, int target, char channel,
			int lun, u_int tag, role_t role, uint32_t status)
{
	return 0;
}