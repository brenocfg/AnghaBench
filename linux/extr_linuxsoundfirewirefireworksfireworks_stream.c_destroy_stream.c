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
struct snd_efw {struct cmp_connection in_conn; struct cmp_connection out_conn; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_destroy (struct amdtp_stream*) ; 
 int /*<<< orphan*/  cmp_connection_destroy (struct cmp_connection*) ; 

__attribute__((used)) static void
destroy_stream(struct snd_efw *efw, struct amdtp_stream *stream)
{
	struct cmp_connection *conn;

	if (stream == &efw->tx_stream)
		conn = &efw->out_conn;
	else
		conn = &efw->in_conn;

	amdtp_stream_destroy(stream);
	cmp_connection_destroy(conn);
}