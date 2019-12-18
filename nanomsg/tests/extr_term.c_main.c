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
struct nn_thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 scalar_t__ ETERM ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_errno () ; 
 int /*<<< orphan*/  nn_sleep (int) ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_term () ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worker ; 

int main ()
{
    int rc;
    int s;
    struct nn_thread thread;

    /*  Close the socket with no associated endpoints. */
    s = test_socket (AF_SP, NN_PAIR);
    test_close (s);

    /*  Test nn_term() before nn_close(). */
    nn_thread_init (&thread, worker, NULL);
    nn_sleep (100);
    nn_term ();

    /*  Check that it's not possible to create new sockets after nn_term(). */
    rc = nn_socket (AF_SP, NN_PAIR);
    nn_assert (rc == -1);
    errno_assert (nn_errno () == ETERM);

    /*  Wait till worker thread terminates. */
    nn_thread_term (&thread);

    return 0;
}