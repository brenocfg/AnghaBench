#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rate; } ;
struct sdw_stream_runtime {int /*<<< orphan*/  state; TYPE_1__ params; struct sdw_master_runtime* m_rt; } ;
struct sdw_master_runtime {int ch_count; TYPE_3__* stream; struct sdw_bus* bus; } ;
struct sdw_master_prop {int max_freq; } ;
struct sdw_bus_params {int bandwidth; } ;
struct sdw_bus {struct sdw_bus_params params; int /*<<< orphan*/  dev; struct sdw_master_prop prop; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_5__ {int rate; int bps; } ;
struct TYPE_6__ {TYPE_2__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SDW_STREAM_PREPARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int do_bank_switch (struct sdw_stream_runtime*) ; 
 int /*<<< orphan*/  memcpy (struct sdw_bus_params*,struct sdw_bus_params*,int) ; 
 int sdw_prep_deprep_ports (struct sdw_master_runtime*,int) ; 
 int sdw_program_params (struct sdw_bus*) ; 

__attribute__((used)) static int _sdw_prepare_stream(struct sdw_stream_runtime *stream)
{
	struct sdw_master_runtime *m_rt = stream->m_rt;
	struct sdw_bus *bus = m_rt->bus;
	struct sdw_master_prop *prop = NULL;
	struct sdw_bus_params params;
	int ret;

	prop = &bus->prop;
	memcpy(&params, &bus->params, sizeof(params));

	/* TODO: Support Asynchronous mode */
	if ((prop->max_freq % stream->params.rate) != 0) {
		dev_err(bus->dev, "Async mode not supported");
		return -EINVAL;
	}

	/* Increment cumulative bus bandwidth */
	/* TODO: Update this during Device-Device support */
	bus->params.bandwidth += m_rt->stream->params.rate *
		m_rt->ch_count * m_rt->stream->params.bps;

	/* Program params */
	ret = sdw_program_params(bus);
	if (ret < 0) {
		dev_err(bus->dev, "Program params failed: %d", ret);
		goto restore_params;
	}

	ret = do_bank_switch(stream);
	if (ret < 0) {
		dev_err(bus->dev, "Bank switch failed: %d", ret);
		goto restore_params;
	}

	/* Prepare port(s) on the new clock configuration */
	ret = sdw_prep_deprep_ports(m_rt, true);
	if (ret < 0) {
		dev_err(bus->dev, "Prepare port(s) failed ret = %d",
				ret);
		return ret;
	}

	stream->state = SDW_STREAM_PREPARED;

	return ret;

restore_params:
	memcpy(&bus->params, &params, sizeof(params));
	return ret;
}