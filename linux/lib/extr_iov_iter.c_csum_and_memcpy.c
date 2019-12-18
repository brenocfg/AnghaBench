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
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int /*<<< orphan*/  csum_block_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  csum_partial_copy_nocheck (void const*,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __wsum csum_and_memcpy(void *to, const void *from, size_t len,
			      __wsum sum, size_t off)
{
	__wsum next = csum_partial_copy_nocheck(from, to, len, 0);
	return csum_block_add(sum, next, off);
}