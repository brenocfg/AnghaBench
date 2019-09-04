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
typedef  unsigned long t_key ;
struct key_vector {unsigned long key; scalar_t__ pos; } ;

/* Variables and functions */
 scalar_t__ BITS_PER_LONG ; 
 scalar_t__ KEYLENGTH ; 

__attribute__((used)) static inline unsigned long get_index(t_key key, struct key_vector *kv)
{
	unsigned long index = key ^ kv->key;

	if ((BITS_PER_LONG <= KEYLENGTH) && (KEYLENGTH == kv->pos))
		return 0;

	return index >> kv->pos;
}