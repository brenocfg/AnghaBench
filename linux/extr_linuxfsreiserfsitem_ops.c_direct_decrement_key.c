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
struct cpu_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_STAT_DATA ; 
 scalar_t__ cpu_key_k_offset (struct cpu_key*) ; 
 int /*<<< orphan*/  cpu_key_k_offset_dec (struct cpu_key*) ; 
 int /*<<< orphan*/  set_cpu_key_k_type (struct cpu_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void direct_decrement_key(struct cpu_key *key)
{
	cpu_key_k_offset_dec(key);
	if (cpu_key_k_offset(key) == 0)
		set_cpu_key_k_type(key, TYPE_STAT_DATA);
}