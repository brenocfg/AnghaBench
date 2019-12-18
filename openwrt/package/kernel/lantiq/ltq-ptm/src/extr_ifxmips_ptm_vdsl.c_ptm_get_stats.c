#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device_stats {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* itf; } ;
struct TYPE_3__ {struct net_device_stats stats; } ;

/* Variables and functions */
 struct net_device** g_net_dev ; 
 TYPE_2__ g_ptm_priv_data ; 

__attribute__((used)) static struct net_device_stats *ptm_get_stats(struct net_device *dev)
{
   struct net_device_stats *s;
  
    if ( dev != g_net_dev[0] )
        return NULL;
s = &g_ptm_priv_data.itf[0].stats;

    return s;
}