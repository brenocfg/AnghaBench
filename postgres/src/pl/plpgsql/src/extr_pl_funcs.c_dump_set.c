#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* expr; } ;
struct TYPE_4__ {char* query; } ;
typedef  TYPE_2__ PLpgSQL_stmt_set ;

/* Variables and functions */
 int /*<<< orphan*/  dump_ind () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
dump_set(PLpgSQL_stmt_set *stmt)
{
	dump_ind();
	printf("%s\n", stmt->expr->query);
}