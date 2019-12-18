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
struct TYPE_5__ {TYPE_1__* method; } ;
struct TYPE_4__ {int /*<<< orphan*/  const* (* get_cipher_by_char ) (unsigned char const*) ;} ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  const* stub1 (unsigned char const*) ; 

const SSL_CIPHER *SSL_CIPHER_find(SSL *ssl, const unsigned char *ptr)
{
    return ssl->method->get_cipher_by_char(ptr);
}