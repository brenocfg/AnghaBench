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
struct sdw_stream_runtime {int /*<<< orphan*/  state; struct sdw_master_runtime* m_rt; } ;
struct sdw_master_runtime {int ch_count; TYPE_3__* stream; struct sdw_bus* bus; } ;
struct TYPE_4__ {int bandwidth; } ;
struct sdw_bus {int /*<<< orphan*/  dev; TYPE_1__ params; } ;
struct TYPE_5__ {int rate; int bps; } ;
struct TYPE_6__ {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDW_STREAM_DEPREPARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int do_bank_switch (struct sdw_stream_runtime*) ; 
 int sdw_prep_deprep_ports (struct sdw_master_runtime*,int) ; 
 int sdw_program_params (struct sdw_bus*) ; 

__attribute__((used)) static int _sdw_deprepare_stream(struct sdw_stream_runtime *stream)
{
	struct sdw_master_runtime *m_rt = stream->m_rt;
	struct sdw_bus *bus = m_rt->bus;
	int ret = 0;

	/* De-prepare port(s) */
	ret = sdw_prep_deprep_ports(m_rt, false);
	if (ret < 0) {
		dev_err(bus->dev, "De-prepare port(s) failed: %d", ret);
		return ret;
	}

	stream->state = SDW_STREAM_DEPREPARED;

	/* TODO: Update this during Device-Device support */
	bus->params.bandwidth -= m_rt->stream->params.rate *
		m_rt->ch_count * m_rt->stream->params.bps;

	/* Program params */
	ret = sdw_program_params(bus);
	if (ret < 0) {
		dev_err(bus->dev, "Program params failed: %d", ret);
		return ret;
	}

	return do_bank_switch(stream);
}