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
typedef  size_t u8 ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 size_t TX_AC_BE_FIFO ; 
 size_t* ac_to_fifo_mapping ; 

__attribute__((used)) static u8 brcms_ac_to_fifo(u8 ac)
{
	if (ac >= ARRAY_SIZE(ac_to_fifo_mapping))
		return TX_AC_BE_FIFO;
	return ac_to_fifo_mapping[ac];
}