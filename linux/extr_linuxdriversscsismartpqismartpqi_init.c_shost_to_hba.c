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
struct pqi_ctrl_info {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 void* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static inline struct pqi_ctrl_info *shost_to_hba(struct Scsi_Host *shost)
{
	void *hostdata = shost_priv(shost);

	return *((struct pqi_ctrl_info **)hostdata);
}