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
typedef  int connect_phase_t ;
typedef  int /*<<< orphan*/  SSL_TEST_CTX ;
typedef  int /*<<< orphan*/  PEER ;

/* Variables and functions */
#define  APPLICATION_DATA 134 
#define  CONNECTION_DONE 133 
#define  HANDSHAKE 132 
#define  RENEG_APPLICATION_DATA 131 
#define  RENEG_HANDSHAKE 130 
#define  RENEG_SETUP 129 
#define  SHUTDOWN 128 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  do_app_data_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_handshake_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_reneg_setup_step (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_shutdown_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_connect_step(const SSL_TEST_CTX *test_ctx, PEER *peer,
                            connect_phase_t phase)
{
    switch (phase) {
    case HANDSHAKE:
        do_handshake_step(peer);
        break;
    case RENEG_APPLICATION_DATA:
        do_app_data_step(peer);
        break;
    case RENEG_SETUP:
        do_reneg_setup_step(test_ctx, peer);
        break;
    case RENEG_HANDSHAKE:
        do_handshake_step(peer);
        break;
    case APPLICATION_DATA:
        do_app_data_step(peer);
        break;
    case SHUTDOWN:
        do_shutdown_step(peer);
        break;
    case CONNECTION_DONE:
        TEST_error("Action after connection done");
        break;
    }
}