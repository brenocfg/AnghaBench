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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  int /*<<< orphan*/ * MYSQL_ROW ;
typedef  int /*<<< orphan*/  MYSQL_RES ;
typedef  TYPE_1__ MYSQLI_WARNING ;
typedef  int /*<<< orphan*/  MYSQL ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mysql_fetch_row (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mysql_free_result (int /*<<< orphan*/ *) ; 
 scalar_t__ mysql_real_query (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * mysql_store_result (int /*<<< orphan*/ *) ; 
 TYPE_1__* php_new_warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

MYSQLI_WARNING *php_get_warnings(MYSQL *mysql)
{
	MYSQLI_WARNING *w, *first = NULL, *prev = NULL;
	MYSQL_RES		*result;
	MYSQL_ROW 		row;

	if (mysql_real_query(mysql, "SHOW WARNINGS", 13)) {
		return NULL;
	}

	result = mysql_store_result(mysql);

	while ((row = mysql_fetch_row(result))) {
		w = php_new_warning(row[2], atoi(row[1]));
		if (!first) {
			first = w;
		}
		if (prev) {
			prev->next = w;
		}
		prev = w;
	}
	mysql_free_result(result);
	return first;
}