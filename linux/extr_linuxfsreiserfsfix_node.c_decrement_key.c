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
struct cpu_key {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* decrement_key ) (struct cpu_key*) ;} ;

/* Variables and functions */
 size_t cpu_key_k_type (struct cpu_key*) ; 
 TYPE_1__** item_ops ; 
 int /*<<< orphan*/  stub1 (struct cpu_key*) ; 

__attribute__((used)) static void decrement_key(struct cpu_key *key)
{
	/* call item specific function for this key */
	item_ops[cpu_key_k_type(key)]->decrement_key(key);
}