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
struct TYPE_6__ {TYPE_1__* method; } ;
struct TYPE_5__ {int (* bwrite_old ) (TYPE_2__*,char const*,int) ;} ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 size_t INT_MAX ; 
 int stub1 (TYPE_2__*,char const*,int) ; 

int bwrite_conv(BIO *bio, const char *data, size_t datal, size_t *written)
{
    int ret;

    if (datal > INT_MAX)
        datal = INT_MAX;

    ret = bio->method->bwrite_old(bio, data, (int)datal);

    if (ret <= 0) {
        *written = 0;
        return ret;
    }

    *written = (size_t)ret;

    return 1;
}