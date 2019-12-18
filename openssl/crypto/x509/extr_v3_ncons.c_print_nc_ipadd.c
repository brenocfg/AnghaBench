#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* data; int length; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int print_nc_ipadd(BIO *bp, ASN1_OCTET_STRING *ip)
{
    int i, len;
    unsigned char *p;
    p = ip->data;
    len = ip->length;
    BIO_puts(bp, "IP:");
    if (len == 8) {
        BIO_printf(bp, "%d.%d.%d.%d/%d.%d.%d.%d",
                   p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
    } else if (len == 32) {
        for (i = 0; i < 16; i++) {
            BIO_printf(bp, "%X", p[0] << 8 | p[1]);
            p += 2;
            if (i == 7)
                BIO_puts(bp, "/");
            else if (i != 15)
                BIO_puts(bp, ":");
        }
    } else
        BIO_printf(bp, "IP Address:<invalid>");
    return 1;
}