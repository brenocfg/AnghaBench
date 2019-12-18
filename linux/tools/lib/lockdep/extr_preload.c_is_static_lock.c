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
struct lock_lookup {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct lock_lookup*) ; 
 struct lock_lookup* __locks ; 

__attribute__((used)) static inline bool is_static_lock(struct lock_lookup *lock)
{
	return lock >= __locks && lock < __locks + ARRAY_SIZE(__locks);
}