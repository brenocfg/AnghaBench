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
struct db_stmt {int (* bind ) (struct db_stmt const*,struct db_row*,size_t) ;} ;
struct db_row {int dummy; } ;

/* Variables and functions */
 int stub1 (struct db_stmt const*,struct db_row*,size_t) ; 

inline bool db_stmt_bind(const struct db_stmt *stmt, struct db_row *rows, size_t n_rows)
{
    return stmt->bind(stmt, rows, n_rows);
}