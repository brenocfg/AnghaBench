#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cmp_connection {scalar_t__ direction; int /*<<< orphan*/  pcr_index; } ;
struct amdtp_stream {int dummy; } ;
struct snd_oxfw {TYPE_1__* unit; struct cmp_connection in_conn; struct cmp_connection out_conn; struct amdtp_stream tx_stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ CMP_OUTPUT ; 
 int EBUSY ; 
 int /*<<< orphan*/  amdtp_stream_running (struct amdtp_stream*) ; 
 int cmp_connection_check_used (struct cmp_connection*,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_connection_used_by_others(struct snd_oxfw *oxfw,
					   struct amdtp_stream *stream)
{
	struct cmp_connection *conn;
	bool used;
	int err;

	if (stream == &oxfw->tx_stream)
		conn = &oxfw->out_conn;
	else
		conn = &oxfw->in_conn;

	err = cmp_connection_check_used(conn, &used);
	if ((err >= 0) && used && !amdtp_stream_running(stream)) {
		dev_err(&oxfw->unit->device,
			"Connection established by others: %cPCR[%d]\n",
			(conn->direction == CMP_OUTPUT) ? 'o' : 'i',
			conn->pcr_index);
		err = -EBUSY;
	}

	return err;
}