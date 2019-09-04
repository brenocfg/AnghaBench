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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  generate_session_id; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  GEN_SESSION_CB ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 

int SSL_set_generate_session_id(SSL *ssl, GEN_SESSION_CB cb)
{
    CRYPTO_THREAD_write_lock(ssl->lock);
    ssl->generate_session_id = cb;
    CRYPTO_THREAD_unlock(ssl->lock);
    return 1;
}