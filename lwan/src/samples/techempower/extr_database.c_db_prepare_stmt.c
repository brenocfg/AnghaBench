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
struct db_stmt {int dummy; } ;
struct db {struct db_stmt* (* prepare ) (struct db const*,char const*,size_t const) ;} ;

/* Variables and functions */
 struct db_stmt* stub1 (struct db const*,char const*,size_t const) ; 

inline struct db_stmt *db_prepare_stmt(const struct db *db, const char *sql,
    const size_t sql_len)
{
    return db->prepare(db, sql, sql_len);
}