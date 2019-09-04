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
struct TYPE_2__ {int /*<<< orphan*/  private_data; int /*<<< orphan*/  (* sample_reset ) (int /*<<< orphan*/ ) ;} ;
struct snd_sf_list {TYPE_1__ callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_sf_list*) ; 
 int /*<<< orphan*/  lock_preset (struct snd_sf_list*) ; 
 int /*<<< orphan*/  snd_sf_clear (struct snd_sf_list*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_preset (struct snd_sf_list*) ; 

void
snd_sf_free(struct snd_sf_list *sflist)
{
	if (sflist == NULL)
		return;
	
	lock_preset(sflist);
	if (sflist->callback.sample_reset)
		sflist->callback.sample_reset(sflist->callback.private_data);
	snd_sf_clear(sflist);
	unlock_preset(sflist);

	kfree(sflist);
}