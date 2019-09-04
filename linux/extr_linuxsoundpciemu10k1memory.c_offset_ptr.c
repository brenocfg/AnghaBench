#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_emu10k1 {int max_cache_pages; char** page_ptr_table; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static inline void *offset_ptr(struct snd_emu10k1 *emu, int page, int offset)
{
	char *ptr;
	if (snd_BUG_ON(page < 0 || page >= emu->max_cache_pages))
		return NULL;
	ptr = emu->page_ptr_table[page];
	if (! ptr) {
		dev_err(emu->card->dev,
			"access to NULL ptr: page = %d\n", page);
		return NULL;
	}
	ptr += offset & (PAGE_SIZE - 1);
	return (void*)ptr;
}