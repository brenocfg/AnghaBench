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
struct sdw_stream_runtime {TYPE_2__* m_rt; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int _sdw_deprepare_stream (struct sdw_stream_runtime*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

int sdw_deprepare_stream(struct sdw_stream_runtime *stream)
{
	int ret = 0;

	if (!stream) {
		pr_err("SoundWire: Handle not found for stream");
		return -EINVAL;
	}

	mutex_lock(&stream->m_rt->bus->bus_lock);

	ret = _sdw_deprepare_stream(stream);
	if (ret < 0)
		pr_err("De-prepare for stream:%d failed: %d", ret, ret);

	mutex_unlock(&stream->m_rt->bus->bus_lock);
	return ret;
}