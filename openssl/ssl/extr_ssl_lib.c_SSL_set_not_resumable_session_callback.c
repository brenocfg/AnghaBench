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
 int /*<<< orphan*/  SSL_CTRL_SET_NOT_RESUMABLE_SESS_CB ; 
 int /*<<< orphan*/  SSL_callback_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) ()) ; 

void SSL_set_not_resumable_session_callback(SSL *ssl,
                                            int (*cb) (SSL *ssl,
                                                       int is_forward_secure))
{
    SSL_callback_ctrl(ssl, SSL_CTRL_SET_NOT_RESUMABLE_SESS_CB,
                      (void (*)(void))cb);
}