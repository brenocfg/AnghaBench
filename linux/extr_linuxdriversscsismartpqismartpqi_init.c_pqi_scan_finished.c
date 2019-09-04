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
struct pqi_ctrl_info {int /*<<< orphan*/  scan_mutex; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct pqi_ctrl_info* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int pqi_scan_finished(struct Scsi_Host *shost,
	unsigned long elapsed_time)
{
	struct pqi_ctrl_info *ctrl_info;

	ctrl_info = shost_priv(shost);

	return !mutex_is_locked(&ctrl_info->scan_mutex);
}