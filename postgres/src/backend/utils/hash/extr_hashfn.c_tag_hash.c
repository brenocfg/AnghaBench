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
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_any (unsigned char const*,int) ; 

uint32
tag_hash(const void *key, Size keysize)
{
	return DatumGetUInt32(hash_any((const unsigned char *) key,
								   (int) keysize));
}