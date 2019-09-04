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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct airo_info {int /*<<< orphan*/ * fids; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIRO_DEF_MTU ; 
 int /*<<< orphan*/  FLAG_FLASHING ; 
 int /*<<< orphan*/  FLAG_MPI ; 
 int MAX_FIDS ; 
 int SUCCESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mpi_init_descriptors (struct airo_info*) ; 
 int setup_card (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transmit_allocate (struct airo_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int flashrestart(struct airo_info *ai,struct net_device *dev){
	int    i,status;

	ssleep(1);			/* Added 12/7/00 */
	clear_bit (FLAG_FLASHING, &ai->flags);
	if (test_bit(FLAG_MPI, &ai->flags)) {
		status = mpi_init_descriptors(ai);
		if (status != SUCCESS)
			return status;
	}
	status = setup_card(ai, dev->dev_addr, 1);

	if (!test_bit(FLAG_MPI,&ai->flags))
		for( i = 0; i < MAX_FIDS; i++ ) {
			ai->fids[i] = transmit_allocate
				( ai, AIRO_DEF_MTU, i >= MAX_FIDS / 2 );
		}

	ssleep(1);			/* Added 12/7/00 */
	return status;
}