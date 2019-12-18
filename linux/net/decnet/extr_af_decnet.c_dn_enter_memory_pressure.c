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
struct sock {int dummy; } ;

/* Variables and functions */
 int dn_memory_pressure ; 

__attribute__((used)) static void dn_enter_memory_pressure(struct sock *sk)
{
	if (!dn_memory_pressure) {
		dn_memory_pressure = 1;
	}
}