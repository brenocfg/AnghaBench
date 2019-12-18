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
struct tls_multi {int /*<<< orphan*/ * session; struct tls_multi* remote_ciphername; int /*<<< orphan*/  locked_cert_hash_set; struct tls_multi* locked_username; struct tls_multi* locked_cn; struct tls_multi* peer_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct tls_multi*) ; 
 int TM_SIZE ; 
 int /*<<< orphan*/  auth_set_client_reason (struct tls_multi*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cert_hash_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tls_multi*) ; 
 int /*<<< orphan*/  secure_memzero (struct tls_multi*,int) ; 
 int /*<<< orphan*/  tls_session_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wipe_auth_token (struct tls_multi*) ; 

void
tls_multi_free(struct tls_multi *multi, bool clear)
{
    int i;

    ASSERT(multi);

#if P2MP_SERVER
    auth_set_client_reason(multi, NULL);

    free(multi->peer_info);
#endif

    if (multi->locked_cn)
    {
        free(multi->locked_cn);
    }

    if (multi->locked_username)
    {
        free(multi->locked_username);
    }

    cert_hash_free(multi->locked_cert_hash_set);

    wipe_auth_token(multi);

    free(multi->remote_ciphername);

    for (i = 0; i < TM_SIZE; ++i)
    {
        tls_session_free(&multi->session[i], false);
    }

    if (clear)
    {
        secure_memzero(multi, sizeof(*multi));
    }

    free(multi);
}