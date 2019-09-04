#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* gpio; } ;
struct onyx {int /*<<< orphan*/  mutex; TYPE_2__ codec; } ;
struct codec_info_item {struct onyx* codec_data; } ;
typedef  enum clock_switch { ____Placeholder_clock_switch } clock_switch ;
struct TYPE_7__ {TYPE_1__* methods; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* all_amps_restore ) (TYPE_3__*) ;int /*<<< orphan*/  (* all_amps_off ) (TYPE_3__*) ;} ;

/* Variables and functions */
#define  CLOCK_SWITCH_PREPARE_SLAVE 129 
#define  CLOCK_SWITCH_SLAVE 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static int onyx_switch_clock(struct codec_info_item *cii,
			     enum clock_switch what)
{
	struct onyx *onyx = cii->codec_data;

	mutex_lock(&onyx->mutex);
	/* this *MUST* be more elaborate later... */
	switch (what) {
	case CLOCK_SWITCH_PREPARE_SLAVE:
		onyx->codec.gpio->methods->all_amps_off(onyx->codec.gpio);
		break;
	case CLOCK_SWITCH_SLAVE:
		onyx->codec.gpio->methods->all_amps_restore(onyx->codec.gpio);
		break;
	default: /* silence warning */
		break;
	}
	mutex_unlock(&onyx->mutex);

	return 0;
}