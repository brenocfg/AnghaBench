#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ db_encoding; int /*<<< orphan*/  db_ctype; int /*<<< orphan*/  db_name; int /*<<< orphan*/  db_collate; } ;
typedef  TYPE_1__ DbInfo ;

/* Variables and functions */
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  equivalent_locale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_encoding_to_char (scalar_t__) ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_locale_and_encoding(DbInfo *olddb, DbInfo *newdb)
{
	if (olddb->db_encoding != newdb->db_encoding)
		pg_fatal("encodings for database \"%s\" do not match:  old \"%s\", new \"%s\"\n",
				 olddb->db_name,
				 pg_encoding_to_char(olddb->db_encoding),
				 pg_encoding_to_char(newdb->db_encoding));
	if (!equivalent_locale(LC_COLLATE, olddb->db_collate, newdb->db_collate))
		pg_fatal("lc_collate values for database \"%s\" do not match:  old \"%s\", new \"%s\"\n",
				 olddb->db_name, olddb->db_collate, newdb->db_collate);
	if (!equivalent_locale(LC_CTYPE, olddb->db_ctype, newdb->db_ctype))
		pg_fatal("lc_ctype values for database \"%s\" do not match:  old \"%s\", new \"%s\"\n",
				 olddb->db_name, olddb->db_ctype, newdb->db_ctype);
}