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
 int ssl_undefined_function (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_undefined_function_3(SSL *ssl, unsigned char *r,
                                    unsigned char *s, size_t t, size_t *u)
{
    (void)r;
    (void)s;
    (void)t;
    (void)u;
    return ssl_undefined_function(ssl);
}