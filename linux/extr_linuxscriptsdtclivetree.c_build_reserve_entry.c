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
typedef  void* uint64_t ;
struct reserve_info {void* size; void* address; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct reserve_info*,int /*<<< orphan*/ ,int) ; 
 struct reserve_info* xmalloc (int) ; 

struct reserve_info *build_reserve_entry(uint64_t address, uint64_t size)
{
	struct reserve_info *new = xmalloc(sizeof(*new));

	memset(new, 0, sizeof(*new));

	new->address = address;
	new->size = size;

	return new;
}