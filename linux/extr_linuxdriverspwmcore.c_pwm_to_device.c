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
struct pwm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pwm_tree ; 
 struct pwm_device* radix_tree_lookup (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static struct pwm_device *pwm_to_device(unsigned int pwm)
{
	return radix_tree_lookup(&pwm_tree, pwm);
}