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
typedef  int u16 ;
struct scsi_device {int id; int channel; int lun; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 lun_from_dev(struct scsi_device *dev)
{
	return (0x2 << 14) | (dev->id << 8) | (dev->channel << 5) | dev->lun;
}