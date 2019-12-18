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

/* Variables and functions */
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 scalar_t__ do_cache ; 
 size_t new_called ; 
 int /*<<< orphan*/ ** sesscache ; 

__attribute__((used)) static int new_cachesession_cb(SSL *ssl, SSL_SESSION *sess)
{
    if (do_cache) {
        sesscache[new_called] = sess;
    } else {
        /* We don't need the reference to the session, so free it */
        SSL_SESSION_free(sess);
    }
    new_called++;

    return 1;
}