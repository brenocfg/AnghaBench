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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  NN_PAIR ; 
 int /*<<< orphan*/  NN_RCVTIMEO ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  NN_WS ; 
 int /*<<< orphan*/  NN_WS_MSG_TYPE ; 
 int NN_WS_MSG_TYPE_TEXT ; 
 int /*<<< orphan*/  socket_address ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  test_bind (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close (int) ; 
 int /*<<< orphan*/  test_connect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_drop (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_recv (int,char*) ; 
 int /*<<< orphan*/  test_send (int,char*) ; 
 int /*<<< orphan*/  test_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int test_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_text ()
{
    int sb;
    int sc;
    int opt;
    uint8_t bad[20];

    /*  Negative testing... bad UTF-8 data for text. */
    sb = test_socket (AF_SP, NN_PAIR);
    sc = test_socket (AF_SP, NN_PAIR);

    opt = NN_WS_MSG_TYPE_TEXT;
    test_setsockopt (sb, NN_WS, NN_WS_MSG_TYPE, &opt, sizeof (opt));
    opt = NN_WS_MSG_TYPE_TEXT;
    test_setsockopt (sc, NN_WS, NN_WS_MSG_TYPE, &opt, sizeof (opt));
    opt = 500;
    test_setsockopt (sb, NN_SOL_SOCKET, NN_RCVTIMEO, &opt, sizeof (opt));

    test_bind (sb, socket_address);
    test_connect (sc, socket_address);

    test_send (sc, "GOOD");
    test_recv (sb, "GOOD");

    /*  and the bad ... */
    strcpy ((char *)bad, "BAD.");
    bad[2] = (char)0xDD;
    test_send (sc, (char *)bad);

    /*  Make sure we dropped the frame. */
    test_drop (sb, ETIMEDOUT);

    test_close (sb);
    test_close (sc);

    return;
}