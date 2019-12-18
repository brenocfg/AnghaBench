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
struct TYPE_5__ {struct TYPE_5__* b; } ;
typedef  TYPE_1__ OPENSSL_LHASH ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_LH_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void OPENSSL_LH_free(OPENSSL_LHASH *lh)
{
    if (lh == NULL)
        return;

    OPENSSL_LH_flush(lh);
    OPENSSL_free(lh->b);
    OPENSSL_free(lh);
}