#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ptr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * info_callback; } ;
typedef  int /*<<< orphan*/  BIO_info_cb ;
typedef  TYPE_1__ BIO_CONNECT ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
#define  BIO_CTRL_SET_CALLBACK 128 

__attribute__((used)) static long conn_callback_ctrl(BIO *b, int cmd, BIO_info_cb *fp)
{
    long ret = 1;
    BIO_CONNECT *data;

    data = (BIO_CONNECT *)b->ptr;

    switch (cmd) {
    case BIO_CTRL_SET_CALLBACK:
        {
            data->info_callback = fp;
        }
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}