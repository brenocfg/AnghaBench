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
 int /*<<< orphan*/  ADDR ; 
 int IPC_CREAT ; 
 int /*<<< orphan*/  IPC_RMID ; 
 unsigned long LENGTH ; 
 int /*<<< orphan*/  SHMAT_FLAGS ; 
 int SHM_HUGETLB ; 
 int SHM_R ; 
 int SHM_W ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* shmat (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ shmdt (void const*) ; 
 int shmget (int,unsigned long,int) ; 

int main(void)
{
	int shmid;
	unsigned long i;
	char *shmaddr;

	shmid = shmget(2, LENGTH, SHM_HUGETLB | IPC_CREAT | SHM_R | SHM_W);
	if (shmid < 0) {
		perror("shmget");
		exit(1);
	}
	printf("shmid: 0x%x\n", shmid);

	shmaddr = shmat(shmid, ADDR, SHMAT_FLAGS);
	if (shmaddr == (char *)-1) {
		perror("Shared memory attach failure");
		shmctl(shmid, IPC_RMID, NULL);
		exit(2);
	}
	printf("shmaddr: %p\n", shmaddr);

	dprintf("Starting the writes:\n");
	for (i = 0; i < LENGTH; i++) {
		shmaddr[i] = (char)(i);
		if (!(i % (1024 * 1024)))
			dprintf(".");
	}
	dprintf("\n");

	dprintf("Starting the Check...");
	for (i = 0; i < LENGTH; i++)
		if (shmaddr[i] != (char)i) {
			printf("\nIndex %lu mismatched\n", i);
			exit(3);
		}
	dprintf("Done.\n");

	if (shmdt((const void *)shmaddr) != 0) {
		perror("Detach failure");
		shmctl(shmid, IPC_RMID, NULL);
		exit(4);
	}

	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}