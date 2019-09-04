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
struct TYPE_3__ {scalar_t__ flags; scalar_t__ init; int /*<<< orphan*/  num; scalar_t__ shutdown; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_closesocket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sock_free(BIO *a)
{
    if (a == NULL)
        return 0;
    if (a->shutdown) {
        if (a->init) {
            BIO_closesocket(a->num);
        }
        a->init = 0;
        a->flags = 0;
    }
    return 1;
}