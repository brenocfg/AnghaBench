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
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,struct async_ctrs*) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int) ; 
 struct async_ctrs* OPENSSL_zalloc (int) ; 

__attribute__((used)) static int async_new(BIO *bio)
{
    struct async_ctrs *ctrs;

    ctrs = OPENSSL_zalloc(sizeof(struct async_ctrs));
    if (ctrs == NULL)
        return 0;

    BIO_set_data(bio, ctrs);
    BIO_set_init(bio, 1);
    return 1;
}