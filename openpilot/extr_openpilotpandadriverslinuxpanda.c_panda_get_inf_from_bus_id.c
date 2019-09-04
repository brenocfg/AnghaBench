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
struct panda_inf_priv {int dummy; } ;
struct panda_dev_priv {struct panda_inf_priv** interfaces; } ;

/* Variables and functions */
 int PANDA_NUM_CAN_INTERFACES ; 
 int* can_numbering ; 

struct panda_inf_priv *
panda_get_inf_from_bus_id(struct panda_dev_priv *priv_dev, int bus_id){
  int inf_num;
  for(inf_num = 0; inf_num < PANDA_NUM_CAN_INTERFACES; inf_num++)
    if(can_numbering[inf_num] == bus_id)
      return priv_dev->interfaces[inf_num];
  return NULL;
}