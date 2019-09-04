#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * next_bio; scalar_t__ ptr; } ;
typedef  int /*<<< orphan*/  BIO_ACCEPT ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (TYPE_1__*) ; 
 int BIO_write (int /*<<< orphan*/ *,char const*,int) ; 
 int acpt_state (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpt_write(BIO *b, const char *in, int inl)
{
    int ret;
    BIO_ACCEPT *data;

    BIO_clear_retry_flags(b);
    data = (BIO_ACCEPT *)b->ptr;

    while (b->next_bio == NULL) {
        ret = acpt_state(b, data);
        if (ret <= 0)
            return ret;
    }

    ret = BIO_write(b->next_bio, in, inl);
    BIO_copy_next_retry(b);
    return ret;
}