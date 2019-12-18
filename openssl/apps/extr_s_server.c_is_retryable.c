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
 int SSL_ERROR_SSL ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_ERROR_ZERO_RETURN ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int is_retryable(SSL *con, int i)
{
    int err = SSL_get_error(con, i);

    /* If it's not a fatal error, it must be retryable */
    return (err != SSL_ERROR_SSL)
           && (err != SSL_ERROR_SYSCALL)
           && (err != SSL_ERROR_ZERO_RETURN);
}