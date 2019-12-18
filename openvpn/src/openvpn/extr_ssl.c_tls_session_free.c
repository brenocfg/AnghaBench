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
struct tls_session {int /*<<< orphan*/  cert_hash_set; scalar_t__ common_name; int /*<<< orphan*/ * key; int /*<<< orphan*/  tls_wrap; } ;

/* Variables and functions */
 size_t KS_SIZE ; 
 int /*<<< orphan*/  cert_hash_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  key_state_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secure_memzero (struct tls_session*,int) ; 
 int /*<<< orphan*/  tls_wrap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_session_free(struct tls_session *session, bool clear)
{
    tls_wrap_free(&session->tls_wrap);

    for (size_t i = 0; i < KS_SIZE; ++i)
    {
        key_state_free(&session->key[i], false);
    }

    if (session->common_name)
    {
        free(session->common_name);
    }

    cert_hash_free(session->cert_hash_set);

    if (clear)
    {
        secure_memzero(session, sizeof(*session));
    }
}