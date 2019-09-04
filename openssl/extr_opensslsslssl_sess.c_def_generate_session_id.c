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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 unsigned int MAX_SESS_ID_ATTEMPTS ; 
 scalar_t__ RAND_bytes (unsigned char*,unsigned int) ; 
 scalar_t__ SSL_has_matching_session_id (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 

__attribute__((used)) static int def_generate_session_id(SSL *ssl, unsigned char *id,
                                   unsigned int *id_len)
{
    unsigned int retry = 0;
    do
        if (RAND_bytes(id, *id_len) <= 0)
            return 0;
    while (SSL_has_matching_session_id(ssl, id, *id_len) &&
           (++retry < MAX_SESS_ID_ATTEMPTS)) ;
    if (retry < MAX_SESS_ID_ATTEMPTS)
        return 1;
    /* else - woops a session_id match */
    /*
     * XXX We should also check the external cache -- but the probability of
     * a collision is negligible, and we could not prevent the concurrent
     * creation of sessions with identical IDs since we currently don't have
     * means to atomically check whether a session ID already exists and make
     * a reservation for it if it does not (this problem applies to the
     * internal cache as well).
     */
    return 0;
}