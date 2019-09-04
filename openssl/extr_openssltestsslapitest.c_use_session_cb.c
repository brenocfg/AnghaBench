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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_SESSION_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clientpsk ; 
 scalar_t__ pskid ; 
 size_t strlen (scalar_t__) ; 
 int use_session_cb_cnt ; 

__attribute__((used)) static int use_session_cb(SSL *ssl, const EVP_MD *md, const unsigned char **id,
                          size_t *idlen, SSL_SESSION **sess)
{
    switch (++use_session_cb_cnt) {
    case 1:
        /* The first call should always have a NULL md */
        if (md != NULL)
            return 0;
        break;

    case 2:
        /* The second call should always have an md */
        if (md == NULL)
            return 0;
        break;

    default:
        /* We should only be called a maximum of twice */
        return 0;
    }

    if (clientpsk != NULL)
        SSL_SESSION_up_ref(clientpsk);

    *sess = clientpsk;
    *id = (const unsigned char *)pskid;
    *idlen = strlen(pskid);

    return 1;
}