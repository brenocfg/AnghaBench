#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long* key; } ;
typedef  TYPE_1__ hsiphash_key_t ;

/* Variables and functions */

__attribute__((used)) static inline void generate_hash_secret(hsiphash_key_t *hash1,
					hsiphash_key_t *hash2)
{
	hash1->key[0] = 2654435761UL;
	hash1->key[1] = 2654435761UL;

	hash2->key[0] = 2654446892UL;
	hash2->key[1] = 2654446892UL;
}