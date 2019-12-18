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
struct async_ctrs {int dummy; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 struct async_ctrs* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (struct async_ctrs*) ; 

__attribute__((used)) static int async_free(BIO *bio)
{
    struct async_ctrs *ctrs;

    if (bio == NULL)
        return 0;
    ctrs = BIO_get_data(bio);
    OPENSSL_free(ctrs);
    BIO_set_data(bio, NULL);
    BIO_set_init(bio, 0);

    return 1;
}