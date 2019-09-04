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
struct fw_unit {int dummy; } ;
struct amdtp_tscm {unsigned int pcm_channels; } ;
struct amdtp_stream {int fdf; struct amdtp_tscm* protocol; } ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;
typedef  int /*<<< orphan*/  amdtp_stream_process_data_blocks_t ;

/* Variables and functions */
 unsigned int AMDTP_FMT_TSCM_RX ; 
 unsigned int AMDTP_FMT_TSCM_TX ; 
 int AMDTP_IN_STREAM ; 
 int CIP_NONBLOCKING ; 
 int CIP_SKIP_DBC_ZERO_CHECK ; 
 int amdtp_stream_init (struct amdtp_stream*,struct fw_unit*,int,int,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_rx_data_blocks ; 
 int /*<<< orphan*/  process_tx_data_blocks ; 

int amdtp_tscm_init(struct amdtp_stream *s, struct fw_unit *unit,
		    enum amdtp_stream_direction dir, unsigned int pcm_channels)
{
	amdtp_stream_process_data_blocks_t process_data_blocks;
	struct amdtp_tscm *p;
	unsigned int fmt;
	int err;

	if (dir == AMDTP_IN_STREAM) {
		fmt = AMDTP_FMT_TSCM_TX;
		process_data_blocks = process_tx_data_blocks;
	} else {
		fmt = AMDTP_FMT_TSCM_RX;
		process_data_blocks = process_rx_data_blocks;
	}

	err = amdtp_stream_init(s, unit, dir,
				CIP_NONBLOCKING | CIP_SKIP_DBC_ZERO_CHECK, fmt,
				process_data_blocks, sizeof(struct amdtp_tscm));
	if (err < 0)
		return 0;

	/* Use fixed value for FDF field. */
	s->fdf = 0x00;

	/* This protocol uses fixed number of data channels for PCM samples. */
	p = s->protocol;
	p->pcm_channels = pcm_channels;

	return 0;
}