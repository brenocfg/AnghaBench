#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 size_t ssl_undefined_function (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t ssl_undefined_function_5(SSL *ssl, const char *r, size_t s,
                                       unsigned char *t)
{
    (void)r;
    (void)s;
    (void)t;
    return ssl_undefined_function(ssl);
}