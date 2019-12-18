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
 int /*<<< orphan*/  NN_PUB ; 
 int /*<<< orphan*/  SOCKET_ADDRESS ; 
 int THREAD_COUNT ; 
 int /*<<< orphan*/  nn_thread_init (struct nn_thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_thread_term (struct nn_thread*) ; 
 int /*<<< orphan*/  routine ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main ()
{
    int sb;
    int i;
    int j;
    struct nn_thread threads [THREAD_COUNT];

    /*  Stress the shutdown algorithm. */

    sb = test_socket (AF_SP, NN_PUB);
    test_bind (sb, SOCKET_ADDRESS);

    for (j = 0; j != 10; ++j) {
        for (i = 0; i != THREAD_COUNT; ++i)
            nn_thread_init (&threads [i], routine, NULL);
        for (i = 0; i != THREAD_COUNT; ++i)
            nn_thread_term (&threads [i]);
    }

    test_close (sb);

    return 0;
}