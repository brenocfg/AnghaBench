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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void* uint32_t ;
struct Swap64 {int /*<<< orphan*/  i; void** ul; } ;

/* Variables and functions */
 void* php_pack_reverse_int32 (void*) ; 

__attribute__((used)) static inline uint64_t php_pack_reverse_int64(uint64_t arg)
{
	union Swap64 {
		uint64_t i;
		uint32_t ul[2];
	} tmp, result;
	tmp.i = arg;
	result.ul[0] = php_pack_reverse_int32(tmp.ul[1]);
	result.ul[1] = php_pack_reverse_int32(tmp.ul[0]);

	return result.i;
}