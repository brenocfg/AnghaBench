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
#define  ECPG_INFORMIX_BAD_DAY 131 
#define  ECPG_INFORMIX_BAD_MONTH 130 
#define  ECPG_INFORMIX_ENOSHORTDATE 129 
#define  ECPG_INFORMIX_ENOTDMY 128 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
check_return(int ret)
{
	switch(ret)
	{
		case ECPG_INFORMIX_ENOTDMY:
			printf("(ECPG_INFORMIX_ENOTDMY)");
			break;
		case ECPG_INFORMIX_ENOSHORTDATE:
			printf("(ECPG_INFORMIX_ENOSHORTDATE)");
			break;
		case ECPG_INFORMIX_BAD_DAY:
			printf("(ECPG_INFORMIX_BAD_DAY)");
			break;
		case ECPG_INFORMIX_BAD_MONTH:
			printf("(ECPG_INFORMIX_BAD_MONTH)");
			break;
		default:
			printf("(unknown ret: %d)", ret);
			break;
	}
	printf("\n");
}