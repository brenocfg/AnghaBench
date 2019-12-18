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
typedef  int /*<<< orphan*/  nn_options_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EFSM ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  NN_MSG ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nn_assert_errno (int,char*) ; 
 int /*<<< orphan*/  nn_freemsg (void*) ; 
 int /*<<< orphan*/  nn_print_message (int /*<<< orphan*/ *,void*,int) ; 
 int nn_recv (int,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nn_recv_loop (nn_options_t *options, int sock)
{
    int rc;
    void *buf;

    for (;;) {
        rc = nn_recv (sock, &buf, NN_MSG, 0);
        if (rc < 0 && errno == EAGAIN) {
            continue;
        } else if (rc < 0 && (errno == ETIMEDOUT || errno == EFSM)) {
            return;  /*  No more messages possible  */
        } else {
            nn_assert_errno (rc >= 0, "Can't recv");
        }
        nn_print_message (options, buf, rc);
        nn_freemsg (buf);
    }
}