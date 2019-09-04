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
struct cmp_connection {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_efw {int /*<<< orphan*/  unit; struct cmp_connection in_conn; struct cmp_connection out_conn; struct amdtp_stream tx_stream; } ;
typedef  enum cmp_direction { ____Placeholder_cmp_direction } cmp_direction ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int AMDTP_OUT_STREAM ; 
 int /*<<< orphan*/  CIP_BLOCKING ; 
 int CMP_INPUT ; 
 int CMP_OUTPUT ; 
 int amdtp_am824_init (struct amdtp_stream*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_destroy (struct amdtp_stream*) ; 
 int /*<<< orphan*/  cmp_connection_destroy (struct cmp_connection*) ; 
 int cmp_connection_init (struct cmp_connection*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_stream(struct snd_efw *efw, struct amdtp_stream *stream)
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
		goto end;

	err = amdtp_am824_init(stream, efw->unit, s_dir, CIP_BLOCKING);
	if (err < 0) {
		amdtp_stream_destroy(stream);
		cmp_connection_destroy(conn);
	}
end:
	return err;
}