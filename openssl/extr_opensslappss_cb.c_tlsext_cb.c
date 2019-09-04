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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_dump (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,char*,char const*,int,int) ; 
 char* lookup (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tlsext_types ; 

void tlsext_cb(SSL *s, int client_server, int type,
               const unsigned char *data, int len, void *arg)
{
    BIO *bio = arg;
    const char *extname = lookup(type, tlsext_types, "unknown");

    BIO_printf(bio, "TLS %s extension \"%s\" (id=%d), len=%d\n",
               client_server ? "server" : "client", extname, type, len);
    BIO_dump(bio, (const char *)data, len);
    (void)BIO_flush(bio);
}