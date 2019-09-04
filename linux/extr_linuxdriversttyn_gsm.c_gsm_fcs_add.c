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
 size_t* gsm_fcs8 ; 

__attribute__((used)) static inline u8 gsm_fcs_add(u8 fcs, u8 c)
{
	return gsm_fcs8[fcs ^ c];
}