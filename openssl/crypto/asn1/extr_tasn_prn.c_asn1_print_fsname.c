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
typedef  int /*<<< orphan*/  spaces ;
struct TYPE_3__ {int flags; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ASN1_PCTX ;

/* Variables and functions */
 int ASN1_PCTX_FLAGS_NO_FIELD_NAME ; 
 int ASN1_PCTX_FLAGS_NO_STRUCT_NAME ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char const*) ; 
 int BIO_write (int /*<<< orphan*/ *,char const*,int const) ; 

__attribute__((used)) static int asn1_print_fsname(BIO *out, int indent,
                             const char *fname, const char *sname,
                             const ASN1_PCTX *pctx)
{
    static const char spaces[] = "                    ";
    static const int nspaces = sizeof(spaces) - 1;

    while (indent > nspaces) {
        if (BIO_write(out, spaces, nspaces) != nspaces)
            return 0;
        indent -= nspaces;
    }
    if (BIO_write(out, spaces, indent) != indent)
        return 0;
    if (pctx->flags & ASN1_PCTX_FLAGS_NO_STRUCT_NAME)
        sname = NULL;
    if (pctx->flags & ASN1_PCTX_FLAGS_NO_FIELD_NAME)
        fname = NULL;
    if (!sname && !fname)
        return 1;
    if (fname) {
        if (BIO_puts(out, fname) <= 0)
            return 0;
    }
    if (sname) {
        if (fname) {
            if (BIO_printf(out, " (%s)", sname) <= 0)
                return 0;
        } else {
            if (BIO_puts(out, sname) <= 0)
                return 0;
        }
    }
    if (BIO_write(out, ": ", 2) != 2)
        return 0;
    return 1;
}