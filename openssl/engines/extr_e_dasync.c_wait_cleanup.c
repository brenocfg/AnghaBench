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
typedef  int /*<<< orphan*/  OSSL_ASYNC_FD ;
typedef  int /*<<< orphan*/  ASYNC_WAIT_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_cleanup(ASYNC_WAIT_CTX *ctx, const void *key,
                         OSSL_ASYNC_FD readfd, void *pvwritefd)
{
    OSSL_ASYNC_FD *pwritefd = (OSSL_ASYNC_FD *)pvwritefd;
#if defined(ASYNC_WIN)
    CloseHandle(readfd);
    CloseHandle(*pwritefd);
#elif defined(ASYNC_POSIX)
    close(readfd);
    close(*pwritefd);
#endif
    OPENSSL_free(pwritefd);
}