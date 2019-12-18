#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * next_bio; scalar_t__ ptr; } ;
struct TYPE_7__ {int lwn; } ;
typedef  TYPE_1__ NBIO_TEST ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_set_retry_write (TYPE_2__*) ; 
 int BIO_write (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ RAND_priv_bytes (unsigned char*,int) ; 

__attribute__((used)) static int nbiof_write(BIO *b, const char *in, int inl)
{
    NBIO_TEST *nt;
    int ret = 0;
    int num;
    unsigned char n;

    if ((in == NULL) || (inl <= 0))
        return 0;
    if (b->next_bio == NULL)
        return 0;
    nt = (NBIO_TEST *)b->ptr;

    BIO_clear_retry_flags(b);

    if (nt->lwn > 0) {
        num = nt->lwn;
        nt->lwn = 0;
    } else {
        if (RAND_priv_bytes(&n, 1) <= 0)
            return -1;
        num = (n & 7);
    }

    if (inl > num)
        inl = num;

    if (num == 0) {
        ret = -1;
        BIO_set_retry_write(b);
    } else {
        ret = BIO_write(b->next_bio, in, inl);
        if (ret < 0) {
            BIO_copy_next_retry(b);
            nt->lwn = inl;
        }
    }
    return ret;
}