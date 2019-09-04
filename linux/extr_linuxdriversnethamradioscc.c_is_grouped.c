#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char group; } ;
struct scc_channel {int* wreg; scalar_t__ dcd; scalar_t__ dev; TYPE_1__ kiss; } ;

/* Variables and functions */
 int Nchips ; 
 size_t R5 ; 
 int RTS ; 
 unsigned char RXGROUP ; 
 struct scc_channel* SCC_Info ; 
 unsigned char TXGROUP ; 

__attribute__((used)) static inline int is_grouped(struct scc_channel *scc)
{
	int k;
	struct scc_channel *scc2;
	unsigned char grp1, grp2;

	grp1 = scc->kiss.group;
	
	for (k = 0; k < (Nchips * 2); k++)
	{
		scc2 = &SCC_Info[k];
		grp2 = scc2->kiss.group;
		
		if (scc2 == scc || !(scc2->dev && grp2))
			continue;
		
		if ((grp1 & 0x3f) == (grp2 & 0x3f))
		{
			if ( (grp1 & TXGROUP) && (scc2->wreg[R5] & RTS) )
				return 1;
			
			if ( (grp1 & RXGROUP) && scc2->dcd )
				return 1;
		}
	}
	return 0;
}