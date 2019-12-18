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
struct TYPE_6__ {void (* msg_callback ) (int,int,int,void const*,size_t,TYPE_2__*,void*) ;TYPE_1__* method; } ;
struct TYPE_5__ {long (* ssl_callback_ctrl ) (TYPE_2__*,int,void (*) ()) ;} ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
#define  SSL_CTRL_SET_MSG_CALLBACK 128 
 long stub1 (TYPE_2__*,int,void (*) ()) ; 

long SSL_callback_ctrl(SSL *s, int cmd, void (*fp) (void))
{
    switch (cmd) {
    case SSL_CTRL_SET_MSG_CALLBACK:
        s->msg_callback = (void (*)
                           (int write_p, int version, int content_type,
                            const void *buf, size_t len, SSL *ssl,
                            void *arg))(fp);
        return 1;

    default:
        return s->method->ssl_callback_ctrl(s, cmd, fp);
    }
}