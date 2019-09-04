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
struct il_priv {TYPE_1__* stations; int /*<<< orphan*/  sta_lock; } ;
struct TYPE_4__ {int tfds_in_queue; } ;
struct TYPE_3__ {TYPE_2__* tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TX (char*,int,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void
il4965_free_tfds_in_queue(struct il_priv *il, int sta_id, int tid, int freed)
{
	lockdep_assert_held(&il->sta_lock);

	if (il->stations[sta_id].tid[tid].tfds_in_queue >= freed)
		il->stations[sta_id].tid[tid].tfds_in_queue -= freed;
	else {
		D_TX("free more than tfds_in_queue (%u:%d)\n",
		     il->stations[sta_id].tid[tid].tfds_in_queue, freed);
		il->stations[sta_id].tid[tid].tfds_in_queue = 0;
	}
}