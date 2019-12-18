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
struct hash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_int ; 
 int /*<<< orphan*/  hash_int_key_cmp ; 
 struct hash* hash_internal_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*),void (*) (void*)) ; 
 void no_op (void*) ; 

struct hash *hash_int_new(void (*free_key)(void *value),
                          void (*free_value)(void *value))
{
    return hash_internal_new(hash_int, hash_int_key_cmp,
                             free_key ? free_key : no_op,
                             free_value ? free_value : no_op);
}