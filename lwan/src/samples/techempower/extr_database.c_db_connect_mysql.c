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
struct TYPE_2__ {int /*<<< orphan*/  prepare; int /*<<< orphan*/  disconnect; } ;
struct db_mysql {int /*<<< orphan*/  con; TYPE_1__ base; } ;
struct db {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_disconnect_mysql ; 
 int /*<<< orphan*/  db_prepare_mysql ; 
 int /*<<< orphan*/  free (struct db_mysql*) ; 
 struct db_mysql* malloc (int) ; 
 int /*<<< orphan*/  mysql_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mysql_real_connect (int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mysql_set_character_set (int /*<<< orphan*/ ,char*) ; 

struct db *db_connect_mysql(const char *host, const char *user, const char *pass,
        const char *database)
{
    struct db_mysql *db_mysql = malloc(sizeof(*db_mysql));

    if (!db_mysql)
        return NULL;

    db_mysql->con = mysql_init(NULL);
    if (!db_mysql->con) {
        free(db_mysql);
        return NULL;
    }

    if (!mysql_real_connect(db_mysql->con, host, user, pass, database, 0, NULL, 0))
        goto error;

    if (mysql_set_character_set(db_mysql->con, "utf8"))
        goto error;

    db_mysql->base.disconnect = db_disconnect_mysql;
    db_mysql->base.prepare = db_prepare_mysql;

    return (struct db *)db_mysql;

error:
    mysql_close(db_mysql->con);
    free(db_mysql);
    return NULL;
}