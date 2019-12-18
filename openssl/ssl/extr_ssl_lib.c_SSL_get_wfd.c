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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TYPE_DESCRIPTOR ; 
 int /*<<< orphan*/ * BIO_find_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_get_fd (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * SSL_get_wbio (int /*<<< orphan*/  const*) ; 

int SSL_get_wfd(const SSL *s)
{
    int ret = -1;
    BIO *b, *r;

    b = SSL_get_wbio(s);
    r = BIO_find_type(b, BIO_TYPE_DESCRIPTOR);
    if (r != NULL)
        BIO_get_fd(r, &ret);
    return ret;
}