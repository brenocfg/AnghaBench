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
struct sdw_stream_runtime {int /*<<< orphan*/ * m_rt; int /*<<< orphan*/  state; } ;
struct sdw_bus {int /*<<< orphan*/  bus_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDW_STREAM_RELEASED ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdw_master_port_release (struct sdw_bus*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdw_release_master_stream (struct sdw_stream_runtime*) ; 

int sdw_stream_remove_master(struct sdw_bus *bus,
		struct sdw_stream_runtime *stream)
{
	mutex_lock(&bus->bus_lock);

	sdw_release_master_stream(stream);
	sdw_master_port_release(bus, stream->m_rt);
	stream->state = SDW_STREAM_RELEASED;
	kfree(stream->m_rt);
	stream->m_rt = NULL;

	mutex_unlock(&bus->bus_lock);

	return 0;
}