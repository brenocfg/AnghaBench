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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int remove_session_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int SSL_CTX_remove_session(SSL_CTX *ctx, SSL_SESSION *c)
{
    return remove_session_lock(ctx, c, 1);
}