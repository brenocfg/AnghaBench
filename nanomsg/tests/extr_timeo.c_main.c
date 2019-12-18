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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  timeo ;
struct nn_stopwatch {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  NN_RCVTIMEO ; 
 int /*<<< orphan*/  NN_SNDTIMEO ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 scalar_t__ nn_errno () ; 
 int nn_recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int nn_send (int,char*,int,int /*<<< orphan*/ ) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  nn_stopwatch_init (struct nn_stopwatch*) ; 
 int /*<<< orphan*/  nn_stopwatch_term (struct nn_stopwatch*) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_assert (int /*<<< orphan*/ ,int) ; 

int main ()
{
    int rc;
    int s;
    int timeo;
    char buf [3];
    struct nn_stopwatch stopwatch;
    uint64_t elapsed;

    s = test_socket (AF_SP, NN_PAIR);

    timeo = 100;
    rc = nn_setsockopt (s, NN_SOL_SOCKET, NN_RCVTIMEO, &timeo, sizeof (timeo));
    errno_assert (rc == 0);
    nn_stopwatch_init (&stopwatch);
    rc = nn_recv (s, buf, sizeof (buf), 0);
    elapsed = nn_stopwatch_term (&stopwatch);
    errno_assert (rc < 0 && nn_errno () == ETIMEDOUT);
    time_assert (elapsed, 100000);

    timeo = 100;
    rc = nn_setsockopt (s, NN_SOL_SOCKET, NN_SNDTIMEO, &timeo, sizeof (timeo));
    errno_assert (rc == 0);
    nn_stopwatch_init (&stopwatch);
    rc = nn_send (s, "ABC", 3, 0);
    elapsed = nn_stopwatch_term (&stopwatch);
    errno_assert (rc < 0 && nn_errno () == ETIMEDOUT);
    time_assert (elapsed, 100000);

    test_close (s);

    return 0;
}