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
struct TYPE_3__ {int dbc_interval; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct amdtp_stream {TYPE_2__ ctx_data; int /*<<< orphan*/  flags; } ;
struct cmp_connection {int dummy; } ;
struct snd_efw {int firmware_version; struct amdtp_stream tx_stream; scalar_t__ is_af9; scalar_t__ is_fireworks3; int /*<<< orphan*/  unit; struct cmp_connection in_conn; struct cmp_connection out_conn; } ;
typedef  enum cmp_direction { ____Placeholder_cmp_direction } cmp_direction ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int AMDTP_OUT_STREAM ; 
 int /*<<< orphan*/  CIP_BLOCKING ; 
 int /*<<< orphan*/  CIP_DBC_IS_END_EVENT ; 
 int /*<<< orphan*/  CIP_EMPTY_WITH_TAG0 ; 
 int /*<<< orphan*/  CIP_SKIP_DBC_ZERO_CHECK ; 
 int /*<<< orphan*/  CIP_UNALIGHED_DBC ; 
 int /*<<< orphan*/  CIP_WRONG_DBS ; 
 int CMP_INPUT ; 
 int CMP_OUTPUT ; 
 int amdtp_am824_init (struct amdtp_stream*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_destroy (struct amdtp_stream*) ; 
 int /*<<< orphan*/  cmp_connection_destroy (struct cmp_connection*) ; 
 int cmp_connection_init (struct cmp_connection*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_stream(struct snd_efw *efw, struct amdtp_stream *stream)
{
	struct cmp_connection *conn;
	enum cmp_direction c_dir;
	enum amdtp_stream_direction s_dir;
	int err;

	if (stream == &efw->tx_stream) {
		conn = &efw->out_conn;
		c_dir = CMP_OUTPUT;
		s_dir = AMDTP_IN_STREAM;
	} else {
		conn = &efw->in_conn;
		c_dir = CMP_INPUT;
		s_dir = AMDTP_OUT_STREAM;
	}

	err = cmp_connection_init(conn, efw->unit, c_dir, 0);
	if (err < 0)
		return err;

	err = amdtp_am824_init(stream, efw->unit, s_dir, CIP_BLOCKING);
	if (err < 0) {
		amdtp_stream_destroy(stream);
		cmp_connection_destroy(conn);
		return err;
	}

	if (stream == &efw->tx_stream) {
		// Fireworks transmits NODATA packets with TAG0.
		efw->tx_stream.flags |= CIP_EMPTY_WITH_TAG0;
		// Fireworks has its own meaning for dbc.
		efw->tx_stream.flags |= CIP_DBC_IS_END_EVENT;
		// Fireworks reset dbc at bus reset.
		efw->tx_stream.flags |= CIP_SKIP_DBC_ZERO_CHECK;
		// But Recent firmwares starts packets with non-zero dbc.
		// Driver version 5.7.6 installs firmware version 5.7.3.
		if (efw->is_fireworks3 &&
		    (efw->firmware_version == 0x5070000 ||
		     efw->firmware_version == 0x5070300 ||
		     efw->firmware_version == 0x5080000))
			efw->tx_stream.flags |= CIP_UNALIGHED_DBC;
		// AudioFire9 always reports wrong dbs.
		if (efw->is_af9)
			efw->tx_stream.flags |= CIP_WRONG_DBS;
		// Firmware version 5.5 reports fixed interval for dbc.
		if (efw->firmware_version == 0x5050000)
			efw->tx_stream.ctx_data.tx.dbc_interval = 8;
	}

	return err;
}