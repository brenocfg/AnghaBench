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
struct sbitmap_word {int /*<<< orphan*/  depth; int /*<<< orphan*/  cleared; int /*<<< orphan*/  word; } ;
struct sbitmap {unsigned int map_nr; struct sbitmap_word* map; } ;

/* Variables and functions */
 scalar_t__ bitmap_weight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __sbitmap_weight(const struct sbitmap *sb, bool set)
{
	unsigned int i, weight = 0;

	for (i = 0; i < sb->map_nr; i++) {
		const struct sbitmap_word *word = &sb->map[i];

		if (set)
			weight += bitmap_weight(&word->word, word->depth);
		else
			weight += bitmap_weight(&word->cleared, word->depth);
	}
	return weight;
}