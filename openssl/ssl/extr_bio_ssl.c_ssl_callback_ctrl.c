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
struct TYPE_5__ {TYPE_1__* ssl; } ;
struct TYPE_4__ {int /*<<< orphan*/  rbio; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  BIO_info_cb ;
typedef  TYPE_2__ BIO_SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
#define  BIO_CTRL_SET_CALLBACK 128 
 long BIO_callback_ctrl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* BIO_get_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long ssl_callback_ctrl(BIO *b, int cmd, BIO_info_cb *fp)
{
    SSL *ssl;
    BIO_SSL *bs;
    long ret = 1;

    bs = BIO_get_data(b);
    ssl = bs->ssl;
    switch (cmd) {
    case BIO_CTRL_SET_CALLBACK:
        ret = BIO_callback_ctrl(ssl->rbio, cmd, fp);
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}