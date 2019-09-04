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
typedef  int u8 ;

/* Variables and functions */
 int ANT_A ; 
 int ANT_B ; 
 int CHAIN_A ; 
 int CHAIN_B ; 
 int CHAIN_C ; 

__attribute__((used)) static inline u8
il4965_find_first_chain(u8 mask)
{
	if (mask & ANT_A)
		return CHAIN_A;
	if (mask & ANT_B)
		return CHAIN_B;
	return CHAIN_C;
}