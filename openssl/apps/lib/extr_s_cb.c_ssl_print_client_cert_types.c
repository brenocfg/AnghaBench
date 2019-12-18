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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char const*) ; 
 int SSL_get0_certificate_types (int /*<<< orphan*/ *,unsigned char const**) ; 
 int /*<<< orphan*/  cert_type_list ; 
 char* lookup (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ssl_print_client_cert_types(BIO *bio, SSL *s)
{
    const unsigned char *p;
    int i;
    int cert_type_num = SSL_get0_certificate_types(s, &p);
    if (!cert_type_num)
        return;
    BIO_puts(bio, "Client Certificate Types: ");
    for (i = 0; i < cert_type_num; i++) {
        unsigned char cert_type = p[i];
        const char *cname = lookup((int)cert_type, cert_type_list, NULL);

        if (i)
            BIO_puts(bio, ", ");
        if (cname != NULL)
            BIO_puts(bio, cname);
        else
            BIO_printf(bio, "UNKNOWN (%d),", cert_type);
    }
    BIO_puts(bio, "\n");
}