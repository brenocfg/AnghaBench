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
typedef  int /*<<< orphan*/  u_int ;
struct Scsi_Host {int /*<<< orphan*/  sg_tablesize; scalar_t__ can_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLOGICPTI_MAX_SG (int) ; 
 int QLOGICPTI_REQ_QUEUE_LEN ; 
 int REQ_QUEUE_DEPTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_host_busy (struct Scsi_Host*) ; 

__attribute__((used)) static inline void update_can_queue(struct Scsi_Host *host, u_int in_ptr, u_int out_ptr)
{
	/* Temporary workaround until bug is found and fixed (one bug has been found
	   already, but fixing it makes things even worse) -jj */
	int num_free = QLOGICPTI_REQ_QUEUE_LEN - REQ_QUEUE_DEPTH(in_ptr, out_ptr) - 64;
	host->can_queue = scsi_host_busy(host) + num_free;
	host->sg_tablesize = QLOGICPTI_MAX_SG(num_free);
}