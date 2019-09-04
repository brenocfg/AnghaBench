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
struct bio_bio_st {int size; } ;
struct TYPE_3__ {struct bio_bio_st* ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 struct bio_bio_st* OPENSSL_zalloc (int) ; 

__attribute__((used)) static int bio_new(BIO *bio)
{
    struct bio_bio_st *b = OPENSSL_zalloc(sizeof(*b));

    if (b == NULL)
        return 0;

    /* enough for one TLS record (just a default) */
    b->size = 17 * 1024;

    bio->ptr = b;
    return 1;
}