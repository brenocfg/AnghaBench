#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct db_stmt {int dummy; } ;
struct TYPE_2__ {int i; } ;
struct db_row {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  JsonNode ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  db_stmt_bind (struct db_stmt*,struct db_row*,int) ; 
 int /*<<< orphan*/  db_stmt_step (struct db_stmt*,struct db_row*) ; 
 int /*<<< orphan*/  json_append_member (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_mknumber (int) ; 
 int /*<<< orphan*/ * json_mkobject () ; 
 int rand () ; 

__attribute__((used)) static JsonNode *
db_query(struct db_stmt *stmt, struct db_row rows[], struct db_row results[])
{
    JsonNode *object = NULL;
    int id = rand() % 10000;

    rows[0].u.i = id;

    if (UNLIKELY(!db_stmt_bind(stmt, rows, 1)))
        goto out;

    if (UNLIKELY(!db_stmt_step(stmt, results)))
        goto out;

    object = json_mkobject();
    if (UNLIKELY(!object))
        goto out;

    json_append_member(object, "id", json_mknumber(id));
    json_append_member(object, "randomNumber", json_mknumber(results[0].u.i));

out:
    return object;
}