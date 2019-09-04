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
struct fintek_8250 {int pid; } ;

/* Variables and functions */
#define  CHIP_ID_F81216 132 
#define  CHIP_ID_F81216AD 131 
#define  CHIP_ID_F81216H 130 
#define  CHIP_ID_F81865 129 
#define  CHIP_ID_F81866 128 
 int ENODEV ; 
 int F81216_LDN_HIGH ; 
 int F81216_LDN_LOW ; 
 int F81866_LDN_HIGH ; 
 int F81866_LDN_LOW ; 

__attribute__((used)) static int fintek_8250_get_ldn_range(struct fintek_8250 *pdata, int *min,
				     int *max)
{
	switch (pdata->pid) {
	case CHIP_ID_F81865:
	case CHIP_ID_F81866:
		*min = F81866_LDN_LOW;
		*max = F81866_LDN_HIGH;
		return 0;

	case CHIP_ID_F81216AD:
	case CHIP_ID_F81216H:
	case CHIP_ID_F81216:
		*min = F81216_LDN_LOW;
		*max = F81216_LDN_HIGH;
		return 0;
	}

	return -ENODEV;
}