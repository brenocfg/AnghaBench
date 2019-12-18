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
struct mg_str {int /*<<< orphan*/  len; int /*<<< orphan*/  p; } ;
struct mg_connection {int dummy; } ;
struct http_message {int dummy; } ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,char*) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (void*,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void op_del(struct mg_connection *nc, const struct http_message *hm,
                   const struct mg_str *key, void *db) {
  sqlite3_stmt *stmt = NULL;
  int result;
  (void) hm;

  if (sqlite3_prepare_v2(db, "DELETE FROM kv WHERE key = ?;", -1, &stmt,
                         NULL) == SQLITE_OK) {
    sqlite3_bind_text(stmt, 1, key->p, key->len, SQLITE_STATIC);
    result = sqlite3_step(stmt);
    if (result == SQLITE_OK || result == SQLITE_ROW) {
      mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");
    } else {
      mg_printf(nc, "%s",
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Length: 0\r\n\r\n");
    }
    sqlite3_finalize(stmt);
  } else {
    mg_printf(nc, "%s",
              "HTTP/1.1 500 Server Error\r\n"
              "Content-Length: 0\r\n\r\n");
  }
}