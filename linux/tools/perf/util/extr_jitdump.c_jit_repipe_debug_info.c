#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nr_entry; int /*<<< orphan*/  entries; } ;
struct TYPE_3__ {int total_size; } ;
union jr_entry {TYPE_2__ info; TYPE_1__ prefix; } ;
struct jit_buf_desc {int /*<<< orphan*/  nr_debug_entries; void* debug_data; } ;

/* Variables and functions */
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int jit_repipe_debug_info(struct jit_buf_desc *jd, union jr_entry *jr)
{
	void *data;
	size_t sz;

	if (!(jd && jr))
		return -1;

	sz  = jr->prefix.total_size - sizeof(jr->info);
	data = malloc(sz);
	if (!data)
		return -1;

	memcpy(data, &jr->info.entries, sz);

	jd->debug_data       = data;

	/*
	 * we must use nr_entry instead of size here because
	 * we cannot distinguish actual entry from padding otherwise
	 */
	jd->nr_debug_entries = jr->info.nr_entry;

	return 0;
}