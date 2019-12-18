#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* method; } ;
struct TYPE_8__ {scalar_t__ valid; } ;
struct TYPE_7__ {TYPE_2__* (* get_cipher_by_char ) (unsigned char const*) ;} ;
typedef  TYPE_2__ SSL_CIPHER ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 TYPE_2__* stub1 (unsigned char const*) ; 

const SSL_CIPHER *ssl_get_cipher_by_char(SSL *ssl, const unsigned char *ptr,
                                         int all)
{
    const SSL_CIPHER *c = ssl->method->get_cipher_by_char(ptr);

    if (c == NULL || (!all && c->valid == 0))
        return NULL;
    return c;
}