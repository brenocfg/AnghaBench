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
struct parport {int dummy; } ;
struct mts64 {TYPE_1__* pardev; } ;
struct TYPE_2__ {struct parport* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTS64_CMD_COM_CLOSE1 ; 
 int /*<<< orphan*/  MTS64_CMD_COM_CLOSE2 ; 
 int /*<<< orphan*/  mts64_write_command (struct parport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mts64_device_close(struct mts64 *mts)
{
	int i;
	struct parport *p = mts->pardev->port;

	for (i = 0; i < 5; ++i) {
		mts64_write_command(p, MTS64_CMD_COM_CLOSE1);
		mts64_write_command(p, MTS64_CMD_COM_CLOSE2);
	}

	return 0;
}