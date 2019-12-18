#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * callback_ex; int /*<<< orphan*/ * callback; TYPE_1__* method; } ;
struct TYPE_6__ {long (* callback_ctrl ) (TYPE_2__*,int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  BIO_info_cb ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int BIO_CB_CTRL ; 
 int BIO_CB_RETURN ; 
 int BIO_CTRL_SET_CALLBACK ; 
 int /*<<< orphan*/  BIO_F_BIO_CALLBACK_CTRL ; 
 int /*<<< orphan*/  BIO_R_UNSUPPORTED_METHOD ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long bio_call_callback (TYPE_2__*,int,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *) ; 
 long stub1 (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

long BIO_callback_ctrl(BIO *b, int cmd, BIO_info_cb *fp)
{
    long ret;

    if (b == NULL)
        return 0;

    if ((b->method == NULL) || (b->method->callback_ctrl == NULL)
            || (cmd != BIO_CTRL_SET_CALLBACK)) {
        BIOerr(BIO_F_BIO_CALLBACK_CTRL, BIO_R_UNSUPPORTED_METHOD);
        return -2;
    }

    if (b->callback != NULL || b->callback_ex != NULL) {
        ret = bio_call_callback(b, BIO_CB_CTRL, (void *)&fp, 0, cmd, 0, 1L,
                                NULL);
        if (ret <= 0)
            return ret;
    }

    ret = b->method->callback_ctrl(b, cmd, fp);

    if (b->callback != NULL || b->callback_ex != NULL)
        ret = bio_call_callback(b, BIO_CB_CTRL | BIO_CB_RETURN, (void *)&fp, 0,
                                cmd, 0, ret, NULL);

    return ret;
}