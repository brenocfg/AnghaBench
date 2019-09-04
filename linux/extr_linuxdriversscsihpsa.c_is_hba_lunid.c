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

/* Variables and functions */
 int /*<<< orphan*/  RAID_CTLR_LUNID ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int is_hba_lunid(unsigned char scsi3addr[])
{
	return memcmp(scsi3addr, RAID_CTLR_LUNID, 8) == 0;
}