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
typedef  int u16 ;

/* Variables and functions */
 int DSA_8021Q_SWITCH_ID_MASK ; 
 int DSA_8021Q_SWITCH_ID_SHIFT ; 

int dsa_8021q_rx_switch_id(u16 vid)
{
	return (vid & DSA_8021Q_SWITCH_ID_MASK) >> DSA_8021Q_SWITCH_ID_SHIFT;
}