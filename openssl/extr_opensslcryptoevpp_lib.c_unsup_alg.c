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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_nid2ln (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unsup_alg(BIO *out, const EVP_PKEY *pkey, int indent,
                     const char *kstr)
{
    BIO_indent(out, indent, 128);
    BIO_printf(out, "%s algorithm \"%s\" unsupported\n",
               kstr, OBJ_nid2ln(pkey->type));
    return 1;
}