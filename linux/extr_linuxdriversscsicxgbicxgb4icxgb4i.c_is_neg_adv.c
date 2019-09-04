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
 unsigned int CPL_ERR_KEEPALV_NEG_ADVICE ; 
 unsigned int CPL_ERR_PERSIST_NEG_ADVICE ; 
 unsigned int CPL_ERR_RTX_NEG_ADVICE ; 

__attribute__((used)) static inline bool is_neg_adv(unsigned int status)
{
	return status == CPL_ERR_RTX_NEG_ADVICE ||
		status == CPL_ERR_KEEPALV_NEG_ADVICE ||
		status == CPL_ERR_PERSIST_NEG_ADVICE;
}