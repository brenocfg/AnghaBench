#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * next_bio; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (TYPE_1__*) ; 
 int BIO_write (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int nullf_write(BIO *b, const char *in, int inl)
{
    int ret = 0;

    if ((in == NULL) || (inl <= 0))
        return 0;
    if (b->next_bio == NULL)
        return 0;
    ret = BIO_write(b->next_bio, in, inl);
    BIO_clear_retry_flags(b);
    BIO_copy_next_retry(b);
    return ret;
}