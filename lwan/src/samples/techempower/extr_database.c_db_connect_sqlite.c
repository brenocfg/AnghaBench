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
struct db_sqlite {TYPE_1__ base; int /*<<< orphan*/  sqlite; } ;
struct db {int dummy; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_OPEN_READONLY ; 
 int /*<<< orphan*/  db_disconnect_sqlite ; 
 int /*<<< orphan*/  db_prepare_sqlite ; 
 int /*<<< orphan*/  free (struct db_sqlite*) ; 
 struct db_sqlite* malloc (int) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqlite3_open_v2 (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

struct db *db_connect_sqlite(const char *path, bool read_only, const char *pragmas[])
{
    struct db_sqlite *db_sqlite = malloc(sizeof(*db_sqlite));

    if (!db_sqlite)
        return NULL;

    int flags = read_only ? SQLITE_OPEN_READONLY : 0;
    int ret = sqlite3_open_v2(path, &db_sqlite->sqlite, flags, NULL);
    if (ret != SQLITE_OK) {
        free(db_sqlite);
        return NULL;
    }

    if (pragmas) {
        for (size_t p = 0; pragmas[p]; p++)
            sqlite3_exec(db_sqlite->sqlite, pragmas[p], NULL, NULL, NULL);
    }

    db_sqlite->base.disconnect = db_disconnect_sqlite;
    db_sqlite->base.prepare = db_prepare_sqlite;

    return (struct db *)db_sqlite;
}