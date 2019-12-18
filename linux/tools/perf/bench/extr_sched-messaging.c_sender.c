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
struct sender_context {unsigned int num_fds; int /*<<< orphan*/ * out_fds; int /*<<< orphan*/  wakefd; int /*<<< orphan*/  ready_out; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int DATASIZE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 unsigned int nr_loops ; 
 int /*<<< orphan*/  ready (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void *sender(struct sender_context *ctx)
{
	char data[DATASIZE];
	unsigned int i, j;

	ready(ctx->ready_out, ctx->wakefd);

	/* Now pump to every receiver. */
	for (i = 0; i < nr_loops; i++) {
		for (j = 0; j < ctx->num_fds; j++) {
			int ret, done = 0;

again:
			ret = write(ctx->out_fds[j], data + done,
				    sizeof(data)-done);
			if (ret < 0)
				err(EXIT_FAILURE, "SENDER: write");
			done += ret;
			if (done < DATASIZE)
				goto again;
		}
	}

	return NULL;
}