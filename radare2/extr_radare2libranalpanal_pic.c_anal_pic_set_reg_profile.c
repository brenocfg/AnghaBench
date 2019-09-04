#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cpu; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int anal_pic_midrange_set_reg_profile (TYPE_1__*) ; 
 int anal_pic_pic18_set_reg_profile (TYPE_1__*) ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 

__attribute__((used)) static int anal_pic_set_reg_profile(RAnal *anal) {
	if (anal->cpu && strcasecmp (anal->cpu, "baseline") == 0) {
		// TODO: We are using the midrange profile as the baseline
		return anal_pic_midrange_set_reg_profile (anal);
	}
	if (anal->cpu && strcasecmp (anal->cpu, "midrange") == 0) {
		return anal_pic_midrange_set_reg_profile (anal);
	}
	if (anal->cpu && strcasecmp (anal->cpu, "pic18") == 0) {
		return anal_pic_pic18_set_reg_profile (anal);
	}
	return -1;
}