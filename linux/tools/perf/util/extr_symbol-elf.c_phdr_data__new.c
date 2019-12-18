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
typedef  void* u64 ;
struct phdr_data {int /*<<< orphan*/  offset; void* len; void* addr; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 struct phdr_data* zalloc (int) ; 

__attribute__((used)) static struct phdr_data *phdr_data__new(u64 addr, u64 len, off_t offset)
{
	struct phdr_data *p = zalloc(sizeof(*p));

	if (p) {
		p->addr   = addr;
		p->len    = len;
		p->offset = offset;
	}

	return p;
}