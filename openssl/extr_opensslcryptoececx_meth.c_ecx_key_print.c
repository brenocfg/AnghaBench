#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ecx_key_op_t ;
struct TYPE_10__ {int /*<<< orphan*/ * pubkey; int /*<<< orphan*/ * privkey; } ;
struct TYPE_7__ {TYPE_4__* ecx; } ;
struct TYPE_9__ {TYPE_2__* ameth; TYPE_1__ pkey; } ;
struct TYPE_8__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_3__ EVP_PKEY ;
typedef  TYPE_4__ ECX_KEY ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_PCTX ;

/* Variables and functions */
 scalar_t__ ASN1_buf_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,int,char*,...) ; 
 int /*<<< orphan*/  KEYLEN (TYPE_3__ const*) ; 
 scalar_t__ KEY_OP_PRIVATE ; 
 char* OBJ_nid2ln (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecx_key_print(BIO *bp, const EVP_PKEY *pkey, int indent,
                         ASN1_PCTX *ctx, ecx_key_op_t op)
{
    const ECX_KEY *ecxkey = pkey->pkey.ecx;
    const char *nm = OBJ_nid2ln(pkey->ameth->pkey_id);

    if (op == KEY_OP_PRIVATE) {
        if (ecxkey == NULL || ecxkey->privkey == NULL) {
            if (BIO_printf(bp, "%*s<INVALID PRIVATE KEY>\n", indent, "") <= 0)
                return 0;
            return 1;
        }
        if (BIO_printf(bp, "%*s%s Private-Key:\n", indent, "", nm) <= 0)
            return 0;
        if (BIO_printf(bp, "%*spriv:\n", indent, "") <= 0)
            return 0;
        if (ASN1_buf_print(bp, ecxkey->privkey, KEYLEN(pkey),
                           indent + 4) == 0)
            return 0;
    } else {
        if (ecxkey == NULL) {
            if (BIO_printf(bp, "%*s<INVALID PUBLIC KEY>\n", indent, "") <= 0)
                return 0;
            return 1;
        }
        if (BIO_printf(bp, "%*s%s Public-Key:\n", indent, "", nm) <= 0)
            return 0;
    }
    if (BIO_printf(bp, "%*spub:\n", indent, "") <= 0)
        return 0;

    if (ASN1_buf_print(bp, ecxkey->pubkey, KEYLEN(pkey),
                       indent + 4) == 0)
        return 0;
    return 1;
}