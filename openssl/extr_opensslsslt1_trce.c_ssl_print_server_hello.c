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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,unsigned char const,unsigned char const,...) ; 
 int /*<<< orphan*/  SSL3_MT_SERVER_HELLO ; 
 unsigned int TLS1_3_VERSION ; 
 int /*<<< orphan*/  ssl_ciphers_tbl ; 
 int /*<<< orphan*/  ssl_comp_tbl ; 
 int /*<<< orphan*/  ssl_print_extensions (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_hexbuf (int /*<<< orphan*/ *,int,char*,int,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_random (int /*<<< orphan*/ *,int,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_version (int /*<<< orphan*/ *,int,char*,unsigned char const**,size_t*,unsigned int*) ; 
 int /*<<< orphan*/  ssl_trace_str (unsigned char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_print_server_hello(BIO *bio, int indent,
                                  const unsigned char *msg, size_t msglen)
{
    unsigned int cs;
    unsigned int vers;

    if (!ssl_print_version(bio, indent, "server_version", &msg, &msglen, &vers))
        return 0;
    if (!ssl_print_random(bio, indent, &msg, &msglen))
        return 0;
    if (vers != TLS1_3_VERSION
            && !ssl_print_hexbuf(bio, indent, "session_id", 1, &msg, &msglen))
        return 0;
    if (msglen < 2)
        return 0;
    cs = (msg[0] << 8) | msg[1];
    BIO_indent(bio, indent, 80);
    BIO_printf(bio, "cipher_suite {0x%02X, 0x%02X} %s\n",
               msg[0], msg[1], ssl_trace_str(cs, ssl_ciphers_tbl));
    msg += 2;
    msglen -= 2;
    if (vers != TLS1_3_VERSION) {
        if (msglen < 1)
            return 0;
        BIO_indent(bio, indent, 80);
        BIO_printf(bio, "compression_method: %s (0x%02X)\n",
                   ssl_trace_str(msg[0], ssl_comp_tbl), msg[0]);
        msg++;
        msglen--;
    }
    if (!ssl_print_extensions(bio, indent, 1, SSL3_MT_SERVER_HELLO, &msg,
                              &msglen))
        return 0;
    return 1;
}