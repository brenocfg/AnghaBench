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
typedef  int /*<<< orphan*/  millis ;

/* Variables and functions */
 int /*<<< orphan*/  NN_RCVTIMEO ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  nn_assert_errno (int,char*) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

void nn_set_recv_timeout (int sock, int millis)
{
    int rc;
    rc = nn_setsockopt (sock, NN_SOL_SOCKET, NN_RCVTIMEO,
                       &millis, sizeof (millis));
    nn_assert_errno (rc == 0, "Can't set recv timeout");
}