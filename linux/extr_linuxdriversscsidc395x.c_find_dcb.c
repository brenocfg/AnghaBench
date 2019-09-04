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
typedef  size_t u8 ;
struct DeviceCtlBlk {int dummy; } ;
struct AdapterCtlBlk {struct DeviceCtlBlk*** children; } ;

/* Variables and functions */

__attribute__((used)) static struct DeviceCtlBlk *find_dcb(struct AdapterCtlBlk *acb, u8 id, u8 lun)
{
	return acb->children[id][lun];
}