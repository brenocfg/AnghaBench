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
typedef  int peer_status_t ;
typedef  int /*<<< orphan*/  handshake_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_ERROR ; 
 int /*<<< orphan*/  HANDSHAKE_RETRY ; 
 int /*<<< orphan*/  HANDSHAKE_SUCCESS ; 
 int /*<<< orphan*/  INTERNAL_ERROR ; 
#define  PEER_ERROR 132 
#define  PEER_RETRY 131 
#define  PEER_SUCCESS 130 
#define  PEER_TEST_FAILURE 129 
#define  PEER_WAITING 128 
 int /*<<< orphan*/  SERVER_ERROR ; 

__attribute__((used)) static handshake_status_t handshake_status(peer_status_t last_status,
                                           peer_status_t previous_status,
                                           int client_spoke_last)
{
    switch (last_status) {
    case PEER_TEST_FAILURE:
        return INTERNAL_ERROR;

    case PEER_WAITING:
        /* Shouldn't ever happen */
        return INTERNAL_ERROR;

    case PEER_SUCCESS:
        switch (previous_status) {
        case PEER_TEST_FAILURE:
            return INTERNAL_ERROR;
        case PEER_SUCCESS:
            /* Both succeeded. */
            return HANDSHAKE_SUCCESS;
        case PEER_WAITING:
        case PEER_RETRY:
            /* Let the first peer finish. */
            return HANDSHAKE_RETRY;
        case PEER_ERROR:
            /*
             * Second peer succeeded despite the fact that the first peer
             * already errored. This shouldn't happen.
             */
            return INTERNAL_ERROR;
        }
        break;

    case PEER_RETRY:
        return HANDSHAKE_RETRY;

    case PEER_ERROR:
        switch (previous_status) {
        case PEER_TEST_FAILURE:
            return INTERNAL_ERROR;
        case PEER_WAITING:
            /* The client failed immediately before sending the ClientHello */
            return client_spoke_last ? CLIENT_ERROR : INTERNAL_ERROR;
        case PEER_SUCCESS:
            /*
             * First peer succeeded but second peer errored.
             * TODO(emilia): we should be able to continue here (with some
             * application data?) to ensure the first peer receives the
             * alert / close_notify.
             * (No tests currently exercise this branch.)
             */
            return client_spoke_last ? CLIENT_ERROR : SERVER_ERROR;
        case PEER_RETRY:
            /* We errored; let the peer finish. */
            return HANDSHAKE_RETRY;
        case PEER_ERROR:
            /* Both peers errored. Return the one that errored first. */
            return client_spoke_last ? SERVER_ERROR : CLIENT_ERROR;
        }
    }
    /* Control should never reach here. */
    return INTERNAL_ERROR;
}