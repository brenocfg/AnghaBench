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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__ hdmi ; 
 int hdmi4_read_edid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int hdmi_runtime_get () ; 
 int /*<<< orphan*/  hdmi_runtime_put () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_edid(u8 *buf, int len)
{
	int r;

	mutex_lock(&hdmi.lock);

	r = hdmi_runtime_get();
	BUG_ON(r);

	r = hdmi4_read_edid(&hdmi.core,  buf, len);

	hdmi_runtime_put();
	mutex_unlock(&hdmi.lock);

	return r;
}