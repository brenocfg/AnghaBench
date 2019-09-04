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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void ssl_print_hex(BIO *bio, int indent, const char *name,
                          const unsigned char *msg, size_t msglen)
{
    size_t i;

    BIO_indent(bio, indent, 80);
    BIO_printf(bio, "%s (len=%d): ", name, (int)msglen);
    for (i = 0; i < msglen; i++)
        BIO_printf(bio, "%02X", msg[i]);
    BIO_puts(bio, "\n");
}