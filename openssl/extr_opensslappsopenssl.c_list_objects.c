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
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ NID_undef ; 
 int OBJ_new_nid (int /*<<< orphan*/ ) ; 
 char* OBJ_nid2ln (int) ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int) ; 
 char* OBJ_nid2sn (int) ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/  const*) ; 
 int OBJ_obj2txt (char*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_realloc (char*,int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  bio_out ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void list_objects(void)
{
    int max_nid = OBJ_new_nid(0);
    int i;
    char *oid_buf = NULL;
    int oid_size = 0;

    /* Skip 0, since that's NID_undef */
    for (i = 1; i < max_nid; i++) {
        const ASN1_OBJECT *obj = OBJ_nid2obj(i);
        const char *sn = OBJ_nid2sn(i);
        const char *ln = OBJ_nid2ln(i);
        int n = 0;

        /*
         * If one of the retrieved objects somehow generated an error,
         * we ignore it.  The check for NID_undef below will detect the
         * error and simply skip to the next NID.
         */
        ERR_clear_error();

        if (OBJ_obj2nid(obj) == NID_undef)
            continue;

        if ((n = OBJ_obj2txt(NULL, 0, obj, 1)) == 0) {
            BIO_printf(bio_out, "# None-OID object: %s, %s\n", sn, ln);
            continue;
        }
        if (n < 0)
            break;               /* Error */

        if (n > oid_size) {
            oid_buf = OPENSSL_realloc(oid_buf, n + 1);
            if (oid_buf == NULL) {
                BIO_printf(bio_err, "ERROR: Memory allocation\n");
                break;           /* Error */
            }
            oid_size = n + 1;
        }
        if (OBJ_obj2txt(oid_buf, oid_size, obj, 1) < 0)
            break;               /* Error */
        if (ln == NULL || strcmp(sn, ln) == 0)
            BIO_printf(bio_out, "%s = %s\n", sn, oid_buf);
        else
            BIO_printf(bio_out, "%s = %s, %s\n", sn, ln, oid_buf);
    }

    OPENSSL_free(oid_buf);
}