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
typedef  int u32 ;
struct sembuf {int dummy; } ;
struct kern_ipc_perm {int dummy; } ;

/* Variables and functions */
 int SEM__READ ; 
 int SEM__WRITE ; 
 int ipc_has_perm (struct kern_ipc_perm*,int) ; 

__attribute__((used)) static int selinux_sem_semop(struct kern_ipc_perm *sma,
			     struct sembuf *sops, unsigned nsops, int alter)
{
	u32 perms;

	if (alter)
		perms = SEM__READ | SEM__WRITE;
	else
		perms = SEM__READ;

	return ipc_has_perm(sma, perms);
}