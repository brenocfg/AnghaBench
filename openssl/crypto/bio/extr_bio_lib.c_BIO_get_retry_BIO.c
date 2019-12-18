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
struct TYPE_5__ {int retry_reason; struct TYPE_5__* next_bio; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_should_retry (TYPE_1__*) ; 

BIO *BIO_get_retry_BIO(BIO *bio, int *reason)
{
    BIO *b, *last;

    b = last = bio;
    for (;;) {
        if (!BIO_should_retry(b))
            break;
        last = b;
        b = b->next_bio;
        if (b == NULL)
            break;
    }
    if (reason != NULL)
        *reason = last->retry_reason;
    return last;
}