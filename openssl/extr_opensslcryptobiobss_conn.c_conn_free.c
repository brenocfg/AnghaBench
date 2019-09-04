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
struct TYPE_4__ {scalar_t__ init; scalar_t__ flags; int /*<<< orphan*/ * ptr; scalar_t__ shutdown; } ;
typedef  int /*<<< orphan*/  BIO_CONNECT ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CONNECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conn_close_socket (TYPE_1__*) ; 

__attribute__((used)) static int conn_free(BIO *a)
{
    BIO_CONNECT *data;

    if (a == NULL)
        return 0;
    data = (BIO_CONNECT *)a->ptr;

    if (a->shutdown) {
        conn_close_socket(a);
        BIO_CONNECT_free(data);
        a->ptr = NULL;
        a->flags = 0;
        a->init = 0;
    }
    return 1;
}