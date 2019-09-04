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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int diacr ; 
 unsigned int handle_diacr (struct vc_data*,unsigned int) ; 

__attribute__((used)) static void k_deadunicode(struct vc_data *vc, unsigned int value, char up_flag)
{
	if (up_flag)
		return;

	diacr = (diacr ? handle_diacr(vc, value) : value);
}