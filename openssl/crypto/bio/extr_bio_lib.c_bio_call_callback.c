#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long (* callback_ex ) (TYPE_1__*,int,char const*,size_t,int,long,long,size_t*) ;long (* callback ) (TYPE_1__*,int,char const*,int,long,long) ;} ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int BIO_CB_CTRL ; 
 int BIO_CB_RETURN ; 
 scalar_t__ HAS_LEN_OPER (int) ; 
 size_t INT_MAX ; 
 long stub1 (TYPE_1__*,int,char const*,size_t,int,long,long,size_t*) ; 
 long stub2 (TYPE_1__*,int,char const*,int,long,long) ; 

__attribute__((used)) static long bio_call_callback(BIO *b, int oper, const char *argp, size_t len,
                              int argi, long argl, long inret, size_t *processed)
{
    long ret;
    int bareoper;

    if (b->callback_ex != NULL)
        return b->callback_ex(b, oper, argp, len, argi, argl, inret, processed);

    /* Strip off any BIO_CB_RETURN flag */
    bareoper = oper & ~BIO_CB_RETURN;

    /*
     * We have an old style callback, so we will have to do nasty casts and
     * check for overflows.
     */
    if (HAS_LEN_OPER(bareoper)) {
        /* In this case |len| is set, and should be used instead of |argi| */
        if (len > INT_MAX)
            return -1;

        argi = (int)len;
    }

    if (inret > 0 && (oper & BIO_CB_RETURN) && bareoper != BIO_CB_CTRL) {
        if (*processed > INT_MAX)
            return -1;
        inret = *processed;
    }

    ret = b->callback(b, oper, argp, argi, argl, inret);

    if (ret > 0 && (oper & BIO_CB_RETURN) && bareoper != BIO_CB_CTRL) {
        *processed = (size_t)ret;
        ret = 1;
    }

    return ret;
}