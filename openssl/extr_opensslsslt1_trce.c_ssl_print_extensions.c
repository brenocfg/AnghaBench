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
 int /*<<< orphan*/  BIO_dump_indent (int /*<<< orphan*/ *,char const*,size_t,int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ssl_print_extension (int /*<<< orphan*/ *,int,int,unsigned char,int,unsigned char const*,size_t) ; 

__attribute__((used)) static int ssl_print_extensions(BIO *bio, int indent, int server,
                                unsigned char mt, const unsigned char **msgin,
                                size_t *msginlen)
{
    size_t extslen, msglen = *msginlen;
    const unsigned char *msg = *msgin;

    BIO_indent(bio, indent, 80);
    if (msglen == 0) {
        BIO_puts(bio, "No extensions\n");
        return 1;
    }
    if (msglen < 2)
        return 0;
    extslen = (msg[0] << 8) | msg[1];
    msglen -= 2;
    msg += 2;
    if (extslen == 0) {
        BIO_puts(bio, "No extensions\n");
        *msgin = msg;
        *msginlen = msglen;
        return 1;
    }
    if (extslen > msglen)
        return 0;
    BIO_printf(bio, "extensions, length = %d\n", (int)extslen);
    msglen -= extslen;
    while (extslen > 0) {
        int extype;
        size_t extlen;
        if (extslen < 4)
            return 0;
        extype = (msg[0] << 8) | msg[1];
        extlen = (msg[2] << 8) | msg[3];
        if (extslen < extlen + 4) {
            BIO_printf(bio, "extensions, extype = %d, extlen = %d\n", extype,
                       (int)extlen);
            BIO_dump_indent(bio, (const char *)msg, extslen, indent + 2);
            return 0;
        }
        msg += 4;
        if (!ssl_print_extension(bio, indent + 2, server, mt, extype, msg,
                                 extlen))
            return 0;
        msg += extlen;
        extslen -= extlen + 4;
    }

    *msgin = msg;
    *msginlen = msglen;
    return 1;
}