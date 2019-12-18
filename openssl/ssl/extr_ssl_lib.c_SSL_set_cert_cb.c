#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cert; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ssl_cert_set_cert_cb (int /*<<< orphan*/ ,int (*) (TYPE_1__*,void*),void*) ; 

void SSL_set_cert_cb(SSL *s, int (*cb) (SSL *ssl, void *arg), void *arg)
{
    ssl_cert_set_cert_cb(s->cert, cb, arg);
}