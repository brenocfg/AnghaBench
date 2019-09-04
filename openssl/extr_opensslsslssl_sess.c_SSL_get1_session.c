#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * session; } ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_SESSION_up_ref (int /*<<< orphan*/ *) ; 

SSL_SESSION *SSL_get1_session(SSL *ssl)
/* variant of SSL_get_session: caller really gets something */
{
    SSL_SESSION *sess;
    /*
     * Need to lock this all up rather than just use CRYPTO_add so that
     * somebody doesn't free ssl->session between when we check it's non-null
     * and when we up the reference count.
     */
    CRYPTO_THREAD_read_lock(ssl->lock);
    sess = ssl->session;
    if (sess)
        SSL_SESSION_up_ref(sess);
    CRYPTO_THREAD_unlock(ssl->lock);
    return sess;
}