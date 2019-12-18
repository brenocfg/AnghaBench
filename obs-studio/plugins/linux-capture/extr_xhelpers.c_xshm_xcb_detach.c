#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int shmid; scalar_t__ data; int /*<<< orphan*/  seg; int /*<<< orphan*/  xcb; } ;
typedef  TYPE_1__ xcb_shm_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  shmctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shmdt (scalar_t__) ; 
 int /*<<< orphan*/  xcb_shm_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xshm_xcb_detach(xcb_shm_t *shm)
{
	if (!shm)
		return;

	xcb_shm_detach(shm->xcb, shm->seg);

	if ((char *)shm->data != (char *)-1)
		shmdt(shm->data);

	if (shm->shmid != -1)
		shmctl(shm->shmid, IPC_RMID, NULL);

	bfree(shm);
}