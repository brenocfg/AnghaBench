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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  I365_CSC ; 
 int I365_CSC_BVD1 ; 
 int I365_CSC_BVD2 ; 
 int I365_CSC_DETECT ; 
 int I365_CSC_READY ; 
 int I365_CSC_STSCHG ; 
 int I365_CS_BVD1 ; 
 int I365_CS_BVD2 ; 
 int I365_CS_DETECT ; 
 int I365_CS_READY ; 
 int I365_CS_STSCHG ; 
 int /*<<< orphan*/  I365_INTCTL ; 
 int I365_PC_IOCARD ; 
 int /*<<< orphan*/  I365_STATUS ; 
 unsigned int SS_BATDEAD ; 
 unsigned int SS_BATWARN ; 
 unsigned int SS_DETECT ; 
 unsigned int SS_READY ; 
 unsigned int SS_STSCHG ; 
 int exca_read_byte (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int get_events(int slot)
{
	unsigned int events = 0;
	uint8_t status, csc;

	status = exca_read_byte(slot, I365_STATUS);
	csc = exca_read_byte(slot, I365_CSC);

	if (exca_read_byte(slot, I365_INTCTL) & I365_PC_IOCARD) {
		if ((csc & I365_CSC_STSCHG) && (status & I365_CS_STSCHG))
			events |= SS_STSCHG;
	} else {
		if (csc & (I365_CSC_BVD1 | I365_CSC_BVD2)) {
			if (!(status & I365_CS_BVD1))
				events |= SS_BATDEAD;
			else if ((status & (I365_CS_BVD1 | I365_CS_BVD2)) == I365_CS_BVD1)
				events |= SS_BATWARN;
		}
	}
	if ((csc & I365_CSC_READY) && (status & I365_CS_READY))
		events |= SS_READY;
	if ((csc & I365_CSC_DETECT) && ((status & I365_CS_DETECT) == I365_CS_DETECT))
		events |= SS_DETECT;

	return events;
}