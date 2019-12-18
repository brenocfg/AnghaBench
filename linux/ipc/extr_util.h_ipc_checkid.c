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
struct kern_ipc_perm {scalar_t__ seq; } ;

/* Variables and functions */
 scalar_t__ ipcid_to_seqx (int) ; 

__attribute__((used)) static inline int ipc_checkid(struct kern_ipc_perm *ipcp, int id)
{
	return ipcid_to_seqx(id) != ipcp->seq;
}