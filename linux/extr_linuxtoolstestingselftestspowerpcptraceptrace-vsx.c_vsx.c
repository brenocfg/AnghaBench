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
 int compare_vsx_vmx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* cptr ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fp_load ; 
 int /*<<< orphan*/  fp_load_new ; 
 int /*<<< orphan*/  fp_store ; 
 int /*<<< orphan*/  loadvsx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_id ; 
 scalar_t__ shmat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmdt (void*) ; 
 int /*<<< orphan*/  storevsx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vsx(void)
{
	int ret;

	cptr = (int *)shmat(shm_id, NULL, 0);
	loadvsx(fp_load, 0);
	cptr[1] = 1;

	while (!cptr[0])
		asm volatile("" : : : "memory");
	shmdt((void *) cptr);

	storevsx(fp_store, 0);
	ret = compare_vsx_vmx(fp_store, fp_load_new);
	if (ret)
		exit(1);
	exit(0);
}