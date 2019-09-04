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
struct rtsx_dev {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */

__attribute__((used)) static inline struct rtsx_dev *host_to_rtsx(struct Scsi_Host *host)
{
	return (struct rtsx_dev *)host->hostdata;
}