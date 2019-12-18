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
struct TYPE_3__ {int /*<<< orphan*/ * wbio; int /*<<< orphan*/ * bbio; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 

BIO *SSL_get_wbio(const SSL *s)
{
    if (s->bbio != NULL) {
        /*
         * If |bbio| is active, the true caller-configured BIO is its
         * |next_bio|.
         */
        return BIO_next(s->bbio);
    }
    return s->wbio;
}