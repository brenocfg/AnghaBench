#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct gpio_runtime {TYPE_3__ line_out_notify; TYPE_2__ line_in_notify; TYPE_1__ headphone_notify; scalar_t__ implementation_private; } ;
struct TYPE_8__ {int /*<<< orphan*/  get_master; int /*<<< orphan*/  set_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amp_mute_gpio ; 
 int /*<<< orphan*/  amp_mute_gpio_activestate ; 
 int /*<<< orphan*/  ftr_gpio_all_amps_off (struct gpio_runtime*) ; 
 int /*<<< orphan*/  ftr_gpio_get_master ; 
 int /*<<< orphan*/  ftr_gpio_set_master ; 
 int /*<<< orphan*/  ftr_handle_notify ; 
 scalar_t__ get_gpio (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_irq (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_enable_dual_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  headphone_detect_gpio ; 
 int /*<<< orphan*/  headphone_detect_gpio_activestate ; 
 int /*<<< orphan*/  headphone_detect_irq ; 
 scalar_t__ headphone_detect_node ; 
 int /*<<< orphan*/  headphone_mute_gpio ; 
 int /*<<< orphan*/  headphone_mute_gpio_activestate ; 
 int /*<<< orphan*/  hw_reset_gpio ; 
 int /*<<< orphan*/  hw_reset_gpio_activestate ; 
 int /*<<< orphan*/  linein_detect_gpio ; 
 int /*<<< orphan*/  linein_detect_gpio_activestate ; 
 int /*<<< orphan*/  linein_detect_irq ; 
 scalar_t__ linein_detect_node ; 
 int /*<<< orphan*/  lineout_detect_gpio ; 
 int /*<<< orphan*/  lineout_detect_gpio_activestate ; 
 int /*<<< orphan*/  lineout_detect_irq ; 
 scalar_t__ lineout_detect_node ; 
 int /*<<< orphan*/  lineout_mute_gpio ; 
 int /*<<< orphan*/  lineout_mute_gpio_activestate ; 
 int /*<<< orphan*/  master_mute_gpio ; 
 int /*<<< orphan*/  master_mute_gpio_activestate ; 
 TYPE_4__ methods ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftr_gpio_init(struct gpio_runtime *rt)
{
	get_gpio("headphone-mute", NULL,
		 &headphone_mute_gpio,
		 &headphone_mute_gpio_activestate);
	get_gpio("amp-mute", NULL,
		 &amp_mute_gpio,
		 &amp_mute_gpio_activestate);
	get_gpio("lineout-mute", NULL,
		 &lineout_mute_gpio,
		 &lineout_mute_gpio_activestate);
	get_gpio("hw-reset", "audio-hw-reset",
		 &hw_reset_gpio,
		 &hw_reset_gpio_activestate);
	if (get_gpio("master-mute", NULL,
		     &master_mute_gpio,
		     &master_mute_gpio_activestate)) {
		methods.set_master = ftr_gpio_set_master;
		methods.get_master = ftr_gpio_get_master;
	}

	headphone_detect_node = get_gpio("headphone-detect", NULL,
					 &headphone_detect_gpio,
					 &headphone_detect_gpio_activestate);
	/* go Apple, and thanks for giving these different names
	 * across the board... */
	lineout_detect_node = get_gpio("lineout-detect", "line-output-detect",
				       &lineout_detect_gpio,
				       &lineout_detect_gpio_activestate);
	linein_detect_node = get_gpio("linein-detect", "line-input-detect",
				      &linein_detect_gpio,
				      &linein_detect_gpio_activestate);

	gpio_enable_dual_edge(headphone_detect_gpio);
	gpio_enable_dual_edge(lineout_detect_gpio);
	gpio_enable_dual_edge(linein_detect_gpio);

	get_irq(headphone_detect_node, &headphone_detect_irq);
	get_irq(lineout_detect_node, &lineout_detect_irq);
	get_irq(linein_detect_node, &linein_detect_irq);

	ftr_gpio_all_amps_off(rt);
	rt->implementation_private = 0;
	INIT_DELAYED_WORK(&rt->headphone_notify.work, ftr_handle_notify);
	INIT_DELAYED_WORK(&rt->line_in_notify.work, ftr_handle_notify);
	INIT_DELAYED_WORK(&rt->line_out_notify.work, ftr_handle_notify);
	mutex_init(&rt->headphone_notify.mutex);
	mutex_init(&rt->line_in_notify.mutex);
	mutex_init(&rt->line_out_notify.mutex);
}