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
struct hdspm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_statusRegister2 ; 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_aes_sync_check(struct hdspm *hdspm, int idx)
{
	int status2, lock, sync;
	status2 = hdspm_read(hdspm, HDSPM_statusRegister2);

	lock = (status2 & (0x0080 >> idx)) ? 1 : 0;
	sync = (status2 & (0x8000 >> idx)) ? 1 : 0;

	if (sync)
		return 2;
	else if (lock)
		return 1;
	return 0;
}