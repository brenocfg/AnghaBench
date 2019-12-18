#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int shmid; int /*<<< orphan*/  data; int /*<<< orphan*/  seg; int /*<<< orphan*/ * xcb; } ;
typedef  TYPE_1__ xcb_shm_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int IPC_CREAT ; 
 int /*<<< orphan*/  IPC_PRIVATE ; 
 TYPE_1__* bzalloc (int) ; 
 int /*<<< orphan*/  shmat (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int shmget (int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  xcb_generate_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_shm_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xshm_xcb_detach (TYPE_1__*) ; 

xcb_shm_t *xshm_xcb_attach(xcb_connection_t *xcb, const int w, const int h)
{
	if (!xcb)
		return NULL;

	xcb_shm_t *shm = bzalloc(sizeof(xcb_shm_t));
	shm->xcb = xcb;
	shm->seg = xcb_generate_id(shm->xcb);

	shm->shmid = shmget(IPC_PRIVATE, w * h * 4, IPC_CREAT | 0777);
	if (shm->shmid == -1)
		goto fail;

	xcb_shm_attach(shm->xcb, shm->seg, shm->shmid, false);

	shm->data = shmat(shm->shmid, NULL, 0);

	return shm;
fail:
	xshm_xcb_detach(shm);
	return NULL;
}