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
struct bio_bio_st {scalar_t__ len; scalar_t__ size; } ;
typedef  size_t ossl_ssize_t ;
struct TYPE_4__ {struct bio_bio_st* ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 size_t OSSL_SSIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t bio_nwrite0 (TYPE_1__*,char**) ; 

__attribute__((used)) static ossl_ssize_t bio_nwrite(BIO *bio, char **buf, size_t num_)
{
    struct bio_bio_st *b;
    ossl_ssize_t num, space;

    if (num_ > OSSL_SSIZE_MAX)
        num = OSSL_SSIZE_MAX;
    else
        num = (ossl_ssize_t) num_;

    space = bio_nwrite0(bio, buf);
    if (num > space)
        num = space;
    if (num <= 0)
        return num;
    b = bio->ptr;
    assert(b != NULL);
    b->len += num;
    assert(b->len <= b->size);

    return num;
}