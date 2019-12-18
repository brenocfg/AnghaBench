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
struct snd_ac97 {int /*<<< orphan*/  page_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_INT_PAGING ; 
 int /*<<< orphan*/  AC97_PAGE_MASK ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_ac97_page_restore(struct snd_ac97 *ac97, int page_save)
{
	if (page_save >= 0) {
		snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, page_save);
		mutex_unlock(&ac97->page_mutex); /* unlock paging */
	}
}