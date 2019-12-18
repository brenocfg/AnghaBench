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
struct TYPE_3__ {int num; char* ptr; scalar_t__ flags; scalar_t__ init; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 scalar_t__ BIO_CONNECT_new () ; 
 scalar_t__ INVALID_SOCKET ; 

__attribute__((used)) static int conn_new(BIO *bi)
{
    bi->init = 0;
    bi->num = (int)INVALID_SOCKET;
    bi->flags = 0;
    if ((bi->ptr = (char *)BIO_CONNECT_new()) == NULL)
        return 0;
    else
        return 1;
}