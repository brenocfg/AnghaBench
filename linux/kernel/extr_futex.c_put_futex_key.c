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
typedef  union futex_key {int dummy; } futex_key ;

/* Variables and functions */
 int /*<<< orphan*/  drop_futex_key_refs (union futex_key*) ; 

__attribute__((used)) static inline void put_futex_key(union futex_key *key)
{
	drop_futex_key_refs(key);
}