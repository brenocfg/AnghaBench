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
struct snd_oxfw {struct cmp_connection in_conn; struct cmp_connection out_conn; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_update (struct amdtp_stream*) ; 
 scalar_t__ cmp_connection_update (struct cmp_connection*) ; 
 int /*<<< orphan*/  stop_stream (struct snd_oxfw*,struct amdtp_stream*) ; 

void snd_oxfw_stream_update_simplex(struct snd_oxfw *oxfw,
				    struct amdtp_stream *stream)
{
	struct cmp_connection *conn;

	if (stream == &oxfw->tx_stream)
		conn = &oxfw->out_conn;
	else
		conn = &oxfw->in_conn;

	if (cmp_connection_update(conn) < 0)
		stop_stream(oxfw, stream);
	else
		amdtp_stream_update(stream);
}