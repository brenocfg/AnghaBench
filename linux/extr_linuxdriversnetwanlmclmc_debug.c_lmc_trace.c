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
struct net_device {int dummy; } ;

/* Variables and functions */

void lmc_trace(struct net_device *dev, char *msg){
#ifdef LMC_TRACE
    unsigned long j = jiffies + 3; /* Wait for 50 ms */

    if(in_interrupt()){
        printk("%s: * %s\n", dev->name, msg);
//        while(time_before(jiffies, j+10))
//            ;
    }
    else {
        printk("%s: %s\n", dev->name, msg);
        while(time_before(jiffies, j))
            schedule();
    }
#endif
}