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
struct samsung_rfkill {int type; struct samsung_laptop* samsung; struct rfkill* rfkill; } ;
struct samsung_laptop {TYPE_1__* platform_device; } ;
struct rfkill_ops {int dummy; } ;
struct rfkill {int dummy; } ;
typedef  enum rfkill_type { ____Placeholder_rfkill_type } rfkill_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rfkill* rfkill_alloc (char const*,int /*<<< orphan*/ *,int,struct rfkill_ops const*,struct samsung_rfkill*) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_init_sw_state (struct rfkill*,int) ; 
 int rfkill_register (struct rfkill*) ; 

__attribute__((used)) static int samsung_new_rfkill(struct samsung_laptop *samsung,
			      struct samsung_rfkill *arfkill,
			      const char *name, enum rfkill_type type,
			      const struct rfkill_ops *ops,
			      int blocked)
{
	struct rfkill **rfkill = &arfkill->rfkill;
	int ret;

	arfkill->type = type;
	arfkill->samsung = samsung;

	*rfkill = rfkill_alloc(name, &samsung->platform_device->dev,
			       type, ops, arfkill);

	if (!*rfkill)
		return -EINVAL;

	if (blocked != -1)
		rfkill_init_sw_state(*rfkill, blocked);

	ret = rfkill_register(*rfkill);
	if (ret) {
		rfkill_destroy(*rfkill);
		*rfkill = NULL;
		return ret;
	}
	return 0;
}