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
struct db_stmt {int /*<<< orphan*/  (* finalize ) (struct db_stmt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct db_stmt*) ; 

inline void db_stmt_finalize(struct db_stmt *stmt)
{
    stmt->finalize(stmt);
}