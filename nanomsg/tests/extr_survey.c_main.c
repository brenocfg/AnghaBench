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
typedef  int /*<<< orphan*/  deadline ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 scalar_t__ EFSM ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  NN_RESPONDENT ; 
 int /*<<< orphan*/  NN_SURVEYOR ; 
 int /*<<< orphan*/  NN_SURVEYOR_DEADLINE ; 
 int /*<<< orphan*/  SOCKET_ADDRESS ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 scalar_t__ nn_errno () ; 
 int nn_recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
    int rc;
    int surveyor;
    int respondent1;
    int respondent2;
    int respondent3;
    int deadline;
    char buf [7];

    /*  Test a simple survey with three respondents. */
    surveyor = test_socket (AF_SP, NN_SURVEYOR);
    deadline = 500;
    rc = nn_setsockopt (surveyor, NN_SURVEYOR, NN_SURVEYOR_DEADLINE,
        &deadline, sizeof (deadline));
    errno_assert (rc == 0);
    test_bind (surveyor, SOCKET_ADDRESS);
    respondent1 = test_socket (AF_SP, NN_RESPONDENT);
    test_connect (respondent1, SOCKET_ADDRESS);
    respondent2 = test_socket (AF_SP, NN_RESPONDENT);
    test_connect (respondent2, SOCKET_ADDRESS);
    respondent3 = test_socket (AF_SP, NN_RESPONDENT);
    test_connect (respondent3, SOCKET_ADDRESS);

    /* Check that attempt to recv with no survey pending is EFSM. */
    rc = nn_recv (surveyor, buf, sizeof (buf), 0);
    errno_assert (rc == -1 && nn_errno () == EFSM);

    /*  Send the survey. */
    test_send (surveyor, "ABC");

    /*  First respondent answers. */
    test_recv (respondent1, "ABC");
    test_send (respondent1, "DEF");

    /*  Second respondent answers. */
    test_recv (respondent2, "ABC");
    test_send (respondent2, "DEF");

    /*  Surveyor gets the responses. */
    test_recv (surveyor, "DEF");
    test_recv (surveyor, "DEF");

    /*  There are no more responses. Surveyor hits the deadline. */
    rc = nn_recv (surveyor, buf, sizeof (buf), 0);
    errno_assert (rc == -1 && nn_errno () == ETIMEDOUT);

    /*  Third respondent answers (it have already missed the deadline). */
    test_recv (respondent3, "ABC");
    test_send (respondent3, "GHI");

    /*  Surveyor initiates new survey. */
    test_send (surveyor, "ABC");

    /*  Check that stale response from third respondent is not delivered. */
    rc = nn_recv (surveyor, buf, sizeof (buf), 0);
    errno_assert (rc == -1 && nn_errno () == ETIMEDOUT);

    /* Check that subsequent attempt to recv with no survey pending is EFSM. */
    rc = nn_recv (surveyor, buf, sizeof (buf), 0);
    errno_assert (rc == -1 && nn_errno () == EFSM);

    test_close (surveyor);
    test_close (respondent1);
    test_close (respondent2);
    test_close (respondent3);

    return 0;
}