#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bio_bio_st {struct bio_bio_st* buf; scalar_t__ peer; } ;
struct TYPE_4__ {struct bio_bio_st* ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (struct bio_bio_st*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_destroy_pair (TYPE_1__*) ; 

__attribute__((used)) static int bio_free(BIO *bio)
{
    struct bio_bio_st *b;

    if (bio == NULL)
        return 0;
    b = bio->ptr;

    assert(b != NULL);

    if (b->peer)
        bio_destroy_pair(bio);

    OPENSSL_free(b->buf);
    OPENSSL_free(b);

    return 1;
}