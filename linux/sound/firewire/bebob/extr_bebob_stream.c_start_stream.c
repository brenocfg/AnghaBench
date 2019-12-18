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
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;
struct cmp_connection {int /*<<< orphan*/  speed; TYPE_1__ resources; } ;
struct amdtp_stream {int dummy; } ;
struct snd_bebob {int /*<<< orphan*/  domain; int /*<<< orphan*/ * maudio_special_quirk; struct cmp_connection out_conn; struct cmp_connection in_conn; struct amdtp_stream rx_stream; } ;

/* Variables and functions */
 int amdtp_domain_add_stream (int /*<<< orphan*/ *,struct amdtp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int map_data_channels (struct snd_bebob*,struct amdtp_stream*) ; 

__attribute__((used)) static int
start_stream(struct snd_bebob *bebob, struct amdtp_stream *stream)
{
	struct cmp_connection *conn;
	int err = 0;

	if (stream == &bebob->rx_stream)
		conn = &bebob->in_conn;
	else
		conn = &bebob->out_conn;

	/* channel mapping */
	if (bebob->maudio_special_quirk == NULL) {
		err = map_data_channels(bebob, stream);
		if (err < 0)
			goto end;
	}

	// start amdtp stream.
	err = amdtp_domain_add_stream(&bebob->domain, stream,
				      conn->resources.channel, conn->speed);
end:
	return err;
}