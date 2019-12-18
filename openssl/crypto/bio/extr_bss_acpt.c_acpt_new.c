#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num; char* ptr; int shutdown; scalar_t__ flags; scalar_t__ init; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ BIO_ACCEPT ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPT_S_BEFORE ; 
 TYPE_1__* BIO_ACCEPT_new () ; 
 scalar_t__ INVALID_SOCKET ; 

__attribute__((used)) static int acpt_new(BIO *bi)
{
    BIO_ACCEPT *ba;

    bi->init = 0;
    bi->num = (int)INVALID_SOCKET;
    bi->flags = 0;
    if ((ba = BIO_ACCEPT_new()) == NULL)
        return 0;
    bi->ptr = (char *)ba;
    ba->state = ACPT_S_BEFORE;
    bi->shutdown = 1;
    return 1;
}