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
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void SSL_set0_wbio(SSL *s, BIO *wbio)
{
    /*
     * If the output buffering BIO is still in place, remove it
     */
    if (s->bbio != NULL)
        s->wbio = BIO_pop(s->wbio);

    BIO_free_all(s->wbio);
    s->wbio = wbio;

    /* Re-attach |bbio| to the new |wbio|. */
    if (s->bbio != NULL)
        s->wbio = BIO_push(s->bbio, s->wbio);
}