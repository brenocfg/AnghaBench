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
typedef  int /*<<< orphan*/  op ;

/* Variables and functions */
 int AF_SP ; 
 int /*<<< orphan*/  NN_DOMAIN ; 
 int NN_PAIR ; 
 int /*<<< orphan*/  NN_PROTOCOL ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int test_socket (int,int) ; 

int main ()
{
    int rc;
    int s;
    int op;
    size_t opsz;

    s = test_socket (AF_SP, NN_PAIR);

    opsz = sizeof (op);
    rc = nn_getsockopt (s, NN_SOL_SOCKET, NN_DOMAIN, &op, &opsz);
    errno_assert (rc == 0);
    nn_assert (opsz == sizeof (op));
    nn_assert (op == AF_SP);

    opsz = sizeof (op);
    rc = nn_getsockopt (s, NN_SOL_SOCKET, NN_PROTOCOL, &op, &opsz);
    errno_assert (rc == 0);
    nn_assert (opsz == sizeof (op));
    nn_assert (op == NN_PAIR);

    test_close (s);

    return 0;
}