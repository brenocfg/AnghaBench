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
struct TYPE_2__ {int /*<<< orphan*/  k_objectid; } ;
struct cpu_key {TYPE_1__ on_disk_key; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_ANY ; 
 int /*<<< orphan*/  set_cpu_key_k_offset (struct cpu_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_key_k_type (struct cpu_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_decrement_key(struct cpu_key *key)
{
	key->on_disk_key.k_objectid--;
	set_cpu_key_k_type(key, TYPE_ANY);
	set_cpu_key_k_offset(key, (loff_t)(~0ULL >> 1));
}