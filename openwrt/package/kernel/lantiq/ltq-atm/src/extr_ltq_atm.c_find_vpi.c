#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int conn_table; TYPE_2__* conn; } ;
struct TYPE_5__ {TYPE_1__* vcc; } ;
struct TYPE_4__ {unsigned int vpi; } ;

/* Variables and functions */
 int MAX_PVC_NUMBER ; 
 TYPE_3__ g_atm_priv_data ; 

__attribute__((used)) static inline int find_vpi(unsigned int vpi)
{
	int i;
	unsigned int bit;

	for ( i = 0, bit = 1; i < MAX_PVC_NUMBER; i++, bit <<= 1 ) {
		if ( (g_atm_priv_data.conn_table & bit) != 0
				&& g_atm_priv_data.conn[i].vcc != NULL
				&& vpi == g_atm_priv_data.conn[i].vcc->vpi )
			return i;
	}

	return -1;
}