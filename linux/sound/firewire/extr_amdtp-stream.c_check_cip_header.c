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
typedef  unsigned int u32 ;
struct TYPE_4__ {unsigned int dbc_interval; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;
struct amdtp_stream {int flags; unsigned int sph; unsigned int fmt; unsigned int data_block_quadlets; TYPE_3__* unit; TYPE_2__ ctx_data; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 unsigned int AMDTP_FDF_NO_DATA ; 
 int CIP_DBC_IS_END_EVENT ; 
 unsigned int CIP_DBC_MASK ; 
 unsigned int CIP_DBS_MASK ; 
 unsigned int CIP_DBS_SHIFT ; 
 int CIP_EMPTY_HAS_WRONG_DBC ; 
 unsigned int CIP_EOH ; 
 unsigned int CIP_EOH_MASK ; 
 unsigned int CIP_FDF_MASK ; 
 unsigned int CIP_FDF_SHIFT ; 
 unsigned int CIP_FMT_AM ; 
 unsigned int CIP_FMT_MASK ; 
 unsigned int CIP_FMT_SHIFT ; 
 int CIP_HEADER_WITHOUT_EOH ; 
 int CIP_SKIP_DBC_ZERO_CHECK ; 
 unsigned int CIP_SPH_MASK ; 
 unsigned int CIP_SPH_SHIFT ; 
 unsigned int CIP_SYT_MASK ; 
 int CIP_WRONG_DBS ; 
 int EAGAIN ; 
 int EIO ; 
 int EPROTO ; 
 unsigned int UINT_MAX ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_info_ratelimited (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int check_cip_header(struct amdtp_stream *s, const __be32 *buf,
			    unsigned int payload_length,
			    unsigned int *data_blocks,
			    unsigned int *data_block_counter, unsigned int *syt)
{
	u32 cip_header[2];
	unsigned int sph;
	unsigned int fmt;
	unsigned int fdf;
	unsigned int dbc;
	bool lost;

	cip_header[0] = be32_to_cpu(buf[0]);
	cip_header[1] = be32_to_cpu(buf[1]);

	/*
	 * This module supports 'Two-quadlet CIP header with SYT field'.
	 * For convenience, also check FMT field is AM824 or not.
	 */
	if ((((cip_header[0] & CIP_EOH_MASK) == CIP_EOH) ||
	     ((cip_header[1] & CIP_EOH_MASK) != CIP_EOH)) &&
	    (!(s->flags & CIP_HEADER_WITHOUT_EOH))) {
		dev_info_ratelimited(&s->unit->device,
				"Invalid CIP header for AMDTP: %08X:%08X\n",
				cip_header[0], cip_header[1]);
		return -EAGAIN;
	}

	/* Check valid protocol or not. */
	sph = (cip_header[0] & CIP_SPH_MASK) >> CIP_SPH_SHIFT;
	fmt = (cip_header[1] & CIP_FMT_MASK) >> CIP_FMT_SHIFT;
	if (sph != s->sph || fmt != s->fmt) {
		dev_info_ratelimited(&s->unit->device,
				     "Detect unexpected protocol: %08x %08x\n",
				     cip_header[0], cip_header[1]);
		return -EAGAIN;
	}

	/* Calculate data blocks */
	fdf = (cip_header[1] & CIP_FDF_MASK) >> CIP_FDF_SHIFT;
	if (payload_length < sizeof(__be32) * 2 ||
	    (fmt == CIP_FMT_AM && fdf == AMDTP_FDF_NO_DATA)) {
		*data_blocks = 0;
	} else {
		unsigned int data_block_quadlets =
				(cip_header[0] & CIP_DBS_MASK) >> CIP_DBS_SHIFT;
		/* avoid division by zero */
		if (data_block_quadlets == 0) {
			dev_err(&s->unit->device,
				"Detect invalid value in dbs field: %08X\n",
				cip_header[0]);
			return -EPROTO;
		}
		if (s->flags & CIP_WRONG_DBS)
			data_block_quadlets = s->data_block_quadlets;

		*data_blocks = (payload_length / sizeof(__be32) - 2) /
							data_block_quadlets;
	}

	/* Check data block counter continuity */
	dbc = cip_header[0] & CIP_DBC_MASK;
	if (*data_blocks == 0 && (s->flags & CIP_EMPTY_HAS_WRONG_DBC) &&
	    *data_block_counter != UINT_MAX)
		dbc = *data_block_counter;

	if ((dbc == 0x00 && (s->flags & CIP_SKIP_DBC_ZERO_CHECK)) ||
	    *data_block_counter == UINT_MAX) {
		lost = false;
	} else if (!(s->flags & CIP_DBC_IS_END_EVENT)) {
		lost = dbc != *data_block_counter;
	} else {
		unsigned int dbc_interval;

		if (*data_blocks > 0 && s->ctx_data.tx.dbc_interval > 0)
			dbc_interval = s->ctx_data.tx.dbc_interval;
		else
			dbc_interval = *data_blocks;

		lost = dbc != ((*data_block_counter + dbc_interval) & 0xff);
	}

	if (lost) {
		dev_err(&s->unit->device,
			"Detect discontinuity of CIP: %02X %02X\n",
			*data_block_counter, dbc);
		return -EIO;
	}

	*data_block_counter = dbc;

	*syt = cip_header[1] & CIP_SYT_MASK;

	return 0;
}