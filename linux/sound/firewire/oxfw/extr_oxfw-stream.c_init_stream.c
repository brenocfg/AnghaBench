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
struct amdtp_stream {int /*<<< orphan*/  flags; } ;
struct cmp_connection {int dummy; } ;
struct snd_oxfw {struct amdtp_stream tx_stream; scalar_t__ wrong_dbs; int /*<<< orphan*/  unit; struct cmp_connection in_conn; struct cmp_connection out_conn; } ;
typedef  enum cmp_direction { ____Placeholder_cmp_direction } cmp_direction ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int AMDTP_OUT_STREAM ; 
 int /*<<< orphan*/  CIP_JUMBO_PAYLOAD ; 
 int /*<<< orphan*/  CIP_NONBLOCKING ; 
 int /*<<< orphan*/  CIP_WRONG_DBS ; 
 int CMP_INPUT ; 
 int CMP_OUTPUT ; 
 int amdtp_am824_init (struct amdtp_stream*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_connection_destroy (struct cmp_connection*) ; 
 int cmp_connection_init (struct cmp_connection*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_stream(struct snd_oxfw *oxfw, struct amdtp_stream *stream)
{
	struct cmp_connection *conn;
	enum cmp_direction c_dir;
	enum amdtp_stream_direction s_dir;
	int err;

	if (stream == &oxfw->tx_stream) {
		conn = &oxfw->out_conn;
		c_dir = CMP_OUTPUT;
		s_dir = AMDTP_IN_STREAM;
	} else {
		conn = &oxfw->in_conn;
		c_dir = CMP_INPUT;
		s_dir = AMDTP_OUT_STREAM;
	}

	err = cmp_connection_init(conn, oxfw->unit, c_dir, 0);
	if (err < 0)
		return err;

	err = amdtp_am824_init(stream, oxfw->unit, s_dir, CIP_NONBLOCKING);
	if (err < 0) {
		cmp_connection_destroy(conn);
		return err;
	}

	/*
	 * OXFW starts to transmit packets with non-zero dbc.
	 * OXFW postpone transferring packets till handling any asynchronous
	 * packets. As a result, next isochronous packet includes more data
	 * blocks than IEC 61883-6 defines.
	 */
	if (stream == &oxfw->tx_stream) {
		oxfw->tx_stream.flags |= CIP_JUMBO_PAYLOAD;
		if (oxfw->wrong_dbs)
			oxfw->tx_stream.flags |= CIP_WRONG_DBS;
	}

	return 0;
}