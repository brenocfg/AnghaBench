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

/* Variables and functions */
 int /*<<< orphan*/  FAT_HASH_BITS ; 
 unsigned long hash_32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long fat_dir_hash(int logstart)
{
	return hash_32(logstart, FAT_HASH_BITS);
}