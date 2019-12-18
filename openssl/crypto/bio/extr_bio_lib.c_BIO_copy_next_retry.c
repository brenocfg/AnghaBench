#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  retry_reason; } ;
struct TYPE_5__ {TYPE_3__* next_bio; int /*<<< orphan*/  retry_reason; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_get_retry_flags (TYPE_3__*) ; 
 int /*<<< orphan*/  BIO_set_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 

void BIO_copy_next_retry(BIO *b)
{
    BIO_set_flags(b, BIO_get_retry_flags(b->next_bio));
    b->retry_reason = b->next_bio->retry_reason;
}