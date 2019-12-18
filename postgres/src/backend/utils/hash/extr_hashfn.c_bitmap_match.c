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
typedef  int Size ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  bms_equal (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 

int
bitmap_match(const void *key1, const void *key2, Size keysize)
{
	Assert(keysize == sizeof(Bitmapset *));
	return !bms_equal(*((const Bitmapset *const *) key1),
					  *((const Bitmapset *const *) key2));
}