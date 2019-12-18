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
struct sbitmap {TYPE_1__* map; } ;
struct TYPE_2__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  word; } ;

/* Variables and functions */
 int __sbitmap_get_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  sbitmap_deferred_clear (struct sbitmap*,int) ; 

__attribute__((used)) static int sbitmap_find_bit_in_index(struct sbitmap *sb, int index,
				     unsigned int alloc_hint, bool round_robin)
{
	int nr;

	do {
		nr = __sbitmap_get_word(&sb->map[index].word,
					sb->map[index].depth, alloc_hint,
					!round_robin);
		if (nr != -1)
			break;
		if (!sbitmap_deferred_clear(sb, index))
			break;
	} while (1);

	return nr;
}