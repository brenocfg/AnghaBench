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
struct db_stmt {int (* step ) (struct db_stmt const*,struct db_row*) ;} ;
struct db_row {int dummy; } ;

/* Variables and functions */
 int stub1 (struct db_stmt const*,struct db_row*) ; 

inline bool db_stmt_step(const struct db_stmt *stmt, struct db_row *row)
{
    return stmt->step(stmt, row);
}