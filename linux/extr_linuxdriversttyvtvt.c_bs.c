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
struct vc_data {int vc_pos; scalar_t__ vc_need_wrap; scalar_t__ vc_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  notify_write (struct vc_data*,char) ; 

__attribute__((used)) static inline void bs(struct vc_data *vc)
{
	if (vc->vc_x) {
		vc->vc_pos -= 2;
		vc->vc_x--;
		vc->vc_need_wrap = 0;
		notify_write(vc, '\b');
	}
}