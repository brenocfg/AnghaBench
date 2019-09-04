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
struct sdw_stream_runtime {int /*<<< orphan*/  state; struct sdw_master_runtime* m_rt; } ;
struct sdw_master_runtime {struct sdw_bus* bus; } ;
struct sdw_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDW_STREAM_ENABLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int do_bank_switch (struct sdw_stream_runtime*) ; 
 int sdw_enable_disable_ports (struct sdw_master_runtime*,int) ; 
 int sdw_program_params (struct sdw_bus*) ; 

__attribute__((used)) static int _sdw_enable_stream(struct sdw_stream_runtime *stream)
{
	struct sdw_master_runtime *m_rt = stream->m_rt;
	struct sdw_bus *bus = m_rt->bus;
	int ret;

	/* Program params */
	ret = sdw_program_params(bus);
	if (ret < 0) {
		dev_err(bus->dev, "Program params failed: %d", ret);
		return ret;
	}

	/* Enable port(s) */
	ret = sdw_enable_disable_ports(m_rt, true);
	if (ret < 0) {
		dev_err(bus->dev, "Enable port(s) failed ret: %d", ret);
		return ret;
	}

	ret = do_bank_switch(stream);
	if (ret < 0) {
		dev_err(bus->dev, "Bank switch failed: %d", ret);
		return ret;
	}

	stream->state = SDW_STREAM_ENABLED;
	return 0;
}