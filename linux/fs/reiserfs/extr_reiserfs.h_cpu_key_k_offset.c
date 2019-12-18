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
struct TYPE_2__ {int /*<<< orphan*/  k_offset; } ;
struct cpu_key {TYPE_1__ on_disk_key; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */

__attribute__((used)) static inline loff_t cpu_key_k_offset(const struct cpu_key *key)
{
	return key->on_disk_key.k_offset;
}