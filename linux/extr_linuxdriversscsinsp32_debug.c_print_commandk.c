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
 int COMMAND_SIZE (unsigned char) ; 
 int /*<<< orphan*/  print_opcodek (unsigned char) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void print_commandk (unsigned char *command)
{
	int i,s;
//	printk(KERN_DEBUG);
	print_opcodek(command[0]);
	/*printk(KERN_DEBUG "%s ", __func__);*/
	if ((command[0] >> 5) == 6 ||
	    (command[0] >> 5) == 7 ) {
		s = 12; /* vender specific */
	} else {
		s = COMMAND_SIZE(command[0]);
	}

	for ( i = 1; i < s; ++i) {
		printk("%02x ", command[i]);
	}

	switch (s) {
	case 6:
		printk("LBA=%d len=%d",
		       (((unsigned int)command[1] & 0x0f) << 16) |
		       ( (unsigned int)command[2]         <<  8) |
		       ( (unsigned int)command[3]              ),
		       (unsigned int)command[4]
			);
		break;
	case 10:
		printk("LBA=%d len=%d",
		       ((unsigned int)command[2] << 24) |
		       ((unsigned int)command[3] << 16) |
		       ((unsigned int)command[4] <<  8) |
		       ((unsigned int)command[5]      ),
		       ((unsigned int)command[7] <<  8) |
		       ((unsigned int)command[8]      )
		       );
		break;
	case 12:
		printk("LBA=%d len=%d",
		       ((unsigned int)command[2] << 24) |
		       ((unsigned int)command[3] << 16) |
		       ((unsigned int)command[4] <<  8) |
		       ((unsigned int)command[5]      ),
		       ((unsigned int)command[6] << 24) |
		       ((unsigned int)command[7] << 16) |
		       ((unsigned int)command[8] <<  8) |
		       ((unsigned int)command[9]      )
		       );
		break;
	default:
		break;
	}
	printk("\n");
}