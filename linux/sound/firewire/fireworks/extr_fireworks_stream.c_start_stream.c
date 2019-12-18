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
struct snd_efw {int /*<<< orphan*/  domain; struct cmp_connection in_conn; struct cmp_connection out_conn; struct amdtp_stream tx_stream; } ;

/* Variables and functions */
 int amdtp_domain_add_stream (int /*<<< orphan*/ *,struct amdtp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_connection_break (struct cmp_connection*) ; 
 int cmp_connection_establish (struct cmp_connection*) ; 

__attribute__((used)) static int start_stream(struct snd_efw *efw, struct amdtp_stream *stream,
			unsigned int rate)
{
	struct cmp_connection *conn;
	int err;

	if (stream == &efw->tx_stream)
		conn = &efw->out_conn;
	else
		conn = &efw->in_conn;

	// Establish connection via CMP.
	err = cmp_connection_establish(conn);
	if (err < 0)
		return err;

	// Start amdtp stream.
	err = amdtp_domain_add_stream(&efw->domain, stream,
				      conn->resources.channel, conn->speed);
	if (err < 0) {
		cmp_connection_break(conn);
		return err;
	}

	return 0;
}