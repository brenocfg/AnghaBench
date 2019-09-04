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
struct amdtp_stream {int dummy; } ;
struct snd_efw {int /*<<< orphan*/  in_conn; int /*<<< orphan*/  out_conn; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_pcm_abort (struct amdtp_stream*) ; 
 int /*<<< orphan*/  amdtp_stream_stop (struct amdtp_stream*) ; 
 int /*<<< orphan*/  cmp_connection_break (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
stop_stream(struct snd_efw *efw, struct amdtp_stream *stream)
{
	amdtp_stream_pcm_abort(stream);
	amdtp_stream_stop(stream);

	if (stream == &efw->tx_stream)
		cmp_connection_break(&efw->out_conn);
	else
		cmp_connection_break(&efw->in_conn);
}