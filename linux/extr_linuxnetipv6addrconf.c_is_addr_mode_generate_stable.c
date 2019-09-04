#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ addr_gen_mode; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 scalar_t__ IN6_ADDR_GEN_MODE_RANDOM ; 
 scalar_t__ IN6_ADDR_GEN_MODE_STABLE_PRIVACY ; 

__attribute__((used)) static bool is_addr_mode_generate_stable(struct inet6_dev *idev)
{
	return idev->cnf.addr_gen_mode == IN6_ADDR_GEN_MODE_STABLE_PRIVACY ||
	       idev->cnf.addr_gen_mode == IN6_ADDR_GEN_MODE_RANDOM;
}