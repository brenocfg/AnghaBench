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
struct list_head {int dummy; } ;

/* Variables and functions */
 unsigned long HASH_SIZE ; 
 unsigned long L1_CACHE_BYTES ; 
 struct list_head* chunk_hash_heads ; 

__attribute__((used)) static inline struct list_head *chunk_hash(unsigned long key)
{
	unsigned long n = key / L1_CACHE_BYTES;
	return chunk_hash_heads + n % HASH_SIZE;
}