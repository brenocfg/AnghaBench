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
struct debug_bucket {int dummy; } ;

/* Variables and functions */
 unsigned long ODEBUG_CHUNK_SHIFT ; 
 int /*<<< orphan*/  ODEBUG_HASH_BITS ; 
 unsigned long hash_long (unsigned long,int /*<<< orphan*/ ) ; 
 struct debug_bucket* obj_hash ; 

__attribute__((used)) static struct debug_bucket *get_bucket(unsigned long addr)
{
	unsigned long hash;

	hash = hash_long((addr >> ODEBUG_CHUNK_SHIFT), ODEBUG_HASH_BITS);
	return &obj_hash[hash];
}