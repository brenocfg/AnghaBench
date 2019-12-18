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
typedef  int /*<<< orphan*/  objbuf ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 char* OBJ_nid2ln (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OBJ_obj2txt (char*,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int asn1_print_oid(BIO *out, const ASN1_OBJECT *oid)
{
    char objbuf[80];
    const char *ln;
    ln = OBJ_nid2ln(OBJ_obj2nid(oid));
    if (!ln)
        ln = "";
    OBJ_obj2txt(objbuf, sizeof(objbuf), oid, 1);
    if (BIO_printf(out, "%s (%s)", ln, objbuf) <= 0)
        return 0;
    return 1;
}