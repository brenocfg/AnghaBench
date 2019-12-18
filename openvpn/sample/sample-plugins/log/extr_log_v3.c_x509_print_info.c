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
typedef  int /*<<< orphan*/  X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ ASN1_STRING_to_UTF8 (unsigned char**,int /*<<< orphan*/ *) ; 
 int NID_undef ; 
 char* OBJ_nid2sn (int) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/ * X509_NAME_ENTRY_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_ENTRY_get_object (int /*<<< orphan*/ *) ; 
 int X509_NAME_entry_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_get_entry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 

__attribute__((used)) static void
x509_print_info(X509 *x509crt)
{
    int i, n;
    int fn_nid;
    ASN1_OBJECT *fn;
    ASN1_STRING *val;
    X509_NAME *x509_name;
    X509_NAME_ENTRY *ent;
    const char *objbuf;
    unsigned char *buf = NULL;

    x509_name = X509_get_subject_name(x509crt);
    n = X509_NAME_entry_count(x509_name);
    for (i = 0; i < n; ++i)
    {
        ent = X509_NAME_get_entry(x509_name, i);
        if (!ent)
        {
            continue;
        }
        fn = X509_NAME_ENTRY_get_object(ent);
        if (!fn)
        {
            continue;
        }
        val = X509_NAME_ENTRY_get_data(ent);
        if (!val)
        {
            continue;
        }
        fn_nid = OBJ_obj2nid(fn);
        if (fn_nid == NID_undef)
        {
            continue;
        }
        objbuf = OBJ_nid2sn(fn_nid);
        if (!objbuf)
        {
            continue;
        }
        if (ASN1_STRING_to_UTF8(&buf, val) < 0)
        {
            continue;
        }

        printf("X509 %s: %s\n", objbuf, (char *)buf);
        OPENSSL_free(buf);
    }
}