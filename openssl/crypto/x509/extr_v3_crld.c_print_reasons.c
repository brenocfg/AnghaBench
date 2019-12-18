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
struct TYPE_3__ {char* lname; int /*<<< orphan*/  bitnum; } ;
typedef  TYPE_1__ BIT_STRING_BITNAME ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 scalar_t__ ASN1_BIT_STRING_get_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int,char*,char const*,int,char*) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* reason_flags ; 

__attribute__((used)) static int print_reasons(BIO *out, const char *rname,
                         ASN1_BIT_STRING *rflags, int indent)
{
    int first = 1;
    const BIT_STRING_BITNAME *pbn;
    BIO_printf(out, "%*s%s:\n%*s", indent, "", rname, indent + 2, "");
    for (pbn = reason_flags; pbn->lname; pbn++) {
        if (ASN1_BIT_STRING_get_bit(rflags, pbn->bitnum)) {
            if (first)
                first = 0;
            else
                BIO_puts(out, ", ");
            BIO_puts(out, pbn->lname);
        }
    }
    if (first)
        BIO_puts(out, "<EMPTY>\n");
    else
        BIO_puts(out, "\n");
    return 1;
}