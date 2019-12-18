#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; int /*<<< orphan*/  error; } ;
struct TYPE_5__ {scalar_t__ unique_subject; } ;
struct TYPE_6__ {TYPE_4__* db; TYPE_1__ attributes; } ;
typedef  TYPE_2__ CA_DB ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DB_name ; 
 int /*<<< orphan*/  DB_serial ; 
 int /*<<< orphan*/  LHASH_COMP_FN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LHASH_HASH_FN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXT_DB_create_index (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  index_name ; 
 int /*<<< orphan*/ * index_name_qual ; 
 int /*<<< orphan*/  index_serial ; 

int index_index(CA_DB *db)
{
    if (!TXT_DB_create_index(db->db, DB_serial, NULL,
                             LHASH_HASH_FN(index_serial),
                             LHASH_COMP_FN(index_serial))) {
        BIO_printf(bio_err,
                   "error creating serial number index:(%ld,%ld,%ld)\n",
                   db->db->error, db->db->arg1, db->db->arg2);
        return 0;
    }

    if (db->attributes.unique_subject
        && !TXT_DB_create_index(db->db, DB_name, index_name_qual,
                                LHASH_HASH_FN(index_name),
                                LHASH_COMP_FN(index_name))) {
        BIO_printf(bio_err, "error creating name index:(%ld,%ld,%ld)\n",
                   db->db->error, db->db->arg1, db->db->arg2);
        return 0;
    }
    return 1;
}