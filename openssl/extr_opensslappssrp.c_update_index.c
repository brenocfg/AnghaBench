#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
struct TYPE_4__ {TYPE_3__* db; } ;
typedef  TYPE_1__ CA_DB ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int DB_NUMBER ; 
 int /*<<< orphan*/  OPENSSL_free (char**) ; 
 int /*<<< orphan*/  TXT_DB_insert (TYPE_3__*,char**) ; 
 char** app_malloc (int,char*) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int update_index(CA_DB *db, char **row)
{
    char **irow;
    int i;

    irow = app_malloc(sizeof(*irow) * (DB_NUMBER + 1), "row pointers");
    for (i = 0; i < DB_NUMBER; i++)
        irow[i] = row[i];
    irow[DB_NUMBER] = NULL;

    if (!TXT_DB_insert(db->db, irow)) {
        BIO_printf(bio_err, "failed to update srpvfile\n");
        BIO_printf(bio_err, "TXT_DB error number %ld\n", db->db->error);
        OPENSSL_free(irow);
        return 0;
    }
    return 1;
}