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
struct TYPE_3__ {int /*<<< orphan*/ * bbio; int /*<<< orphan*/  wbio; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_pop (int /*<<< orphan*/ ) ; 

int ssl_free_wbio_buffer(SSL *s)
{
    /* callers ensure s is never null */
    if (s->bbio == NULL)
        return 1;

    s->wbio = BIO_pop(s->wbio);
    BIO_free(s->bbio);
    s->bbio = NULL;

    return 1;
}