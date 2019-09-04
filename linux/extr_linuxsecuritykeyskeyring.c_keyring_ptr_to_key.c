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
struct key {int dummy; } ;
struct assoc_array_ptr {int dummy; } ;

/* Variables and functions */
 unsigned long KEYRING_PTR_SUBTYPE ; 
 void* assoc_array_ptr_to_leaf (struct assoc_array_ptr const*) ; 

__attribute__((used)) static inline struct key *keyring_ptr_to_key(const struct assoc_array_ptr *x)
{
	void *object = assoc_array_ptr_to_leaf(x);
	return (struct key *)((unsigned long)object & ~KEYRING_PTR_SUBTYPE);
}