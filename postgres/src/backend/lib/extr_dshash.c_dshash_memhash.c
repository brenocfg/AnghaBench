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
typedef  int /*<<< orphan*/  dshash_hash ;

/* Variables and functions */
 int /*<<< orphan*/  tag_hash (void const*,size_t) ; 

dshash_hash
dshash_memhash(const void *v, size_t size, void *arg)
{
	return tag_hash(v, size);
}