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
struct session {int /*<<< orphan*/  user; } ;
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
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static void
session_user_set(struct session *sess, X509 *x509)
{
    int fn_nid;
    ASN1_OBJECT *fn;
    ASN1_STRING *val;
    X509_NAME *x509_name;
    X509_NAME_ENTRY *ent;
    const char *objbuf;

    x509_name = X509_get_subject_name(x509);
    int i, n = X509_NAME_entry_count(x509_name);
    for (i = 0; i < n; ++i)
    {
        if (!(ent = X509_NAME_get_entry(x509_name, i)))
        {
            continue;
        }
        if (!(fn = X509_NAME_ENTRY_get_object(ent)))
        {
            continue;
        }
        if (!(val = X509_NAME_ENTRY_get_data(ent)))
        {
            continue;
        }
        if ((fn_nid = OBJ_obj2nid(fn)) == NID_undef)
        {
            continue;
        }
        if (!(objbuf = OBJ_nid2sn(fn_nid)))
        {
            continue;
        }
        unsigned char *buf = NULL;
        if (ASN1_STRING_to_UTF8(&buf, val) < 0)
        {
            continue;
        }

        if (!strncasecmp(objbuf, "CN", 2))
        {
            snprintf(sess->user, sizeof(sess->user) - 1, (char *)buf);
        }

        OPENSSL_free(buf);
    }
}