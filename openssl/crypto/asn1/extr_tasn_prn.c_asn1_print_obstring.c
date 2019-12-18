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
struct TYPE_3__ {scalar_t__ type; int flags; scalar_t__ length; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 scalar_t__ BIO_dump_indent (int /*<<< orphan*/ *,char const*,scalar_t__,int) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ V_ASN1_BIT_STRING ; 

__attribute__((used)) static int asn1_print_obstring(BIO *out, const ASN1_STRING *str, int indent)
{
    if (str->type == V_ASN1_BIT_STRING) {
        if (BIO_printf(out, " (%ld unused bits)\n", str->flags & 0x7) <= 0)
            return 0;
    } else if (BIO_puts(out, "\n") <= 0)
        return 0;
    if ((str->length > 0)
        && BIO_dump_indent(out, (const char *)str->data, str->length,
                           indent + 2) <= 0)
        return 0;
    return 1;
}