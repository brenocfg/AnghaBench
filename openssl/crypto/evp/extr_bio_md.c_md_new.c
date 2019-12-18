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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 

__attribute__((used)) static int md_new(BIO *bi)
{
    EVP_MD_CTX *ctx;

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL)
        return 0;

    BIO_set_init(bi, 1);
    BIO_set_data(bi, ctx);

    return 1;
}