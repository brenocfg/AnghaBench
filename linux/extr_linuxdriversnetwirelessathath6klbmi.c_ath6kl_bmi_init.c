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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ max_data_size; scalar_t__ max_cmd_size; int /*<<< orphan*/  cmd_buf; } ;
struct ath6kl {TYPE_1__ bmi; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

int ath6kl_bmi_init(struct ath6kl *ar)
{
	if (WARN_ON(ar->bmi.max_data_size == 0))
		return -EINVAL;

	/* cmd + addr + len + data_size */
	ar->bmi.max_cmd_size = ar->bmi.max_data_size + (sizeof(u32) * 3);

	ar->bmi.cmd_buf = kzalloc(ar->bmi.max_cmd_size, GFP_KERNEL);
	if (!ar->bmi.cmd_buf)
		return -ENOMEM;

	return 0;
}