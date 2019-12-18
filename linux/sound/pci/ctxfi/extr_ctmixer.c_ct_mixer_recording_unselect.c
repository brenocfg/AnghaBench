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
struct ct_mixer {struct amixer** amixers; } ;
struct amixer {TYPE_1__* ops; } ;
typedef  enum CT_AMIXER_CTL { ____Placeholder_CT_AMIXER_CTL } CT_AMIXER_CTL ;
struct TYPE_2__ {int /*<<< orphan*/  (* commit_write ) (struct amixer*) ;int /*<<< orphan*/  (* set_sum ) (struct amixer*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int CHN_NUM ; 
 int /*<<< orphan*/  stub1 (struct amixer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct amixer*) ; 

__attribute__((used)) static void
ct_mixer_recording_unselect(struct ct_mixer *mixer, enum CT_AMIXER_CTL type)
{
	struct amixer *amix_d;
	int i;

	for (i = 0; i < 2; i++) {
		amix_d = mixer->amixers[type*CHN_NUM+i];
		amix_d->ops->set_sum(amix_d, NULL);
		amix_d->ops->commit_write(amix_d);
	}
}