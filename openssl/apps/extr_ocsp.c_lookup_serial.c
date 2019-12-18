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
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ CA_DB ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_to_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* BN_bn2hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int DB_NUMBER ; 
 size_t DB_serial ; 
 int /*<<< orphan*/  OPENSSL_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char*) ; 
 char** TXT_DB_get_by_index (int /*<<< orphan*/ ,size_t,char**) ; 

__attribute__((used)) static char **lookup_serial(CA_DB *db, ASN1_INTEGER *ser)
{
    int i;
    BIGNUM *bn = NULL;
    char *itmp, *row[DB_NUMBER], **rrow;
    for (i = 0; i < DB_NUMBER; i++)
        row[i] = NULL;
    bn = ASN1_INTEGER_to_BN(ser, NULL);
    OPENSSL_assert(bn);         /* FIXME: should report an error at this
                                 * point and abort */
    if (BN_is_zero(bn))
        itmp = OPENSSL_strdup("00");
    else
        itmp = BN_bn2hex(bn);
    row[DB_serial] = itmp;
    BN_free(bn);
    rrow = TXT_DB_get_by_index(db->db, DB_serial, row);
    OPENSSL_free(itmp);
    return rrow;
}