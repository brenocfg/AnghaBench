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
typedef  scalar_t__ u32 ;
struct vbox_private {int /*<<< orphan*/  guest_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  VBOX_VBVA_CONF32_GUEST_CURSOR_REPORTING ; 
 int /*<<< orphan*/  VBOX_VBVA_CONF32_MODE_HINT_REPORTING ; 
 scalar_t__ VINF_SUCCESS ; 
 int hgsmi_query_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static bool have_hgsmi_mode_hints(struct vbox_private *vbox)
{
	u32 have_hints, have_cursor;
	int ret;

	ret = hgsmi_query_conf(vbox->guest_pool,
			       VBOX_VBVA_CONF32_MODE_HINT_REPORTING,
			       &have_hints);
	if (ret)
		return false;

	ret = hgsmi_query_conf(vbox->guest_pool,
			       VBOX_VBVA_CONF32_GUEST_CURSOR_REPORTING,
			       &have_cursor);
	if (ret)
		return false;

	return have_hints == VINF_SUCCESS && have_cursor == VINF_SUCCESS;
}