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
struct template_mime {int /*<<< orphan*/  tpl; } ;
struct lwan_url_map {char* prefix; int /*<<< orphan*/  member_1; struct template_mime* data; int /*<<< orphan*/  handler; } ;
struct lwan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWAN_HANDLER_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUERIES_PER_HOUR ; 
 int /*<<< orphan*/  SERVE_FILES (char*) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_OPEN_READONLY ; 
 int /*<<< orphan*/  cache ; 
 int /*<<< orphan*/  cache_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cache_destroy (int /*<<< orphan*/ ) ; 
 struct template_mime compile_template (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_ipinfo ; 
 int /*<<< orphan*/  create_query_limit ; 
 int /*<<< orphan*/  csv_template_str ; 
 int /*<<< orphan*/  db ; 
 int /*<<< orphan*/  destroy_ipinfo ; 
 int /*<<< orphan*/  destroy_query_limit ; 
 int /*<<< orphan*/  json_template_str ; 
 int /*<<< orphan*/  lwan_init (struct lwan*) ; 
 int /*<<< orphan*/  lwan_main_loop (struct lwan*) ; 
 int /*<<< orphan*/  lwan_set_url_map (struct lwan*,struct lwan_url_map const*) ; 
 int /*<<< orphan*/  lwan_shutdown (struct lwan*) ; 
 int /*<<< orphan*/  lwan_status_critical (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_status_info (char*,...) ; 
 int /*<<< orphan*/  lwan_tpl_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_limit ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int sqlite3_open_v2 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  templated_output ; 
 int /*<<< orphan*/  xml_template_str ; 

int main(void)
{
    struct lwan l;

    lwan_init(&l);

    struct template_mime json_tpl =
        compile_template(json_template_str, "application/json; charset=UTF-8");
    struct template_mime csv_tpl =
        compile_template(csv_template_str, "application/csv; charset=UTF-8");
    struct template_mime xml_tpl =
        compile_template(xml_template_str, "text/plain; charset=UTF-8");

    int result =
        sqlite3_open_v2("./db/ipdb.sqlite", &db, SQLITE_OPEN_READONLY, NULL);
    if (result != SQLITE_OK)
        lwan_status_critical("Could not open database: %s", sqlite3_errmsg(db));
    cache = cache_create(create_ipinfo, destroy_ipinfo, NULL, 10);

#if QUERIES_PER_HOUR != 0
    lwan_status_info("Limiting to %d queries per hour per client",
                     QUERIES_PER_HOUR);
    query_limit =
        cache_create(create_query_limit, destroy_query_limit, NULL, 3600);
#else
    lwan_status_info("Rate-limiting disabled");
#endif

    const struct lwan_url_map default_map[] = {
        {.prefix = "/json/",
         .handler = LWAN_HANDLER_REF(templated_output),
         .data = &json_tpl},
        {.prefix = "/xml/",
         .handler = LWAN_HANDLER_REF(templated_output),
         .data = &xml_tpl},
        {.prefix = "/csv/",
         .handler = LWAN_HANDLER_REF(templated_output),
         .data = &csv_tpl},
        {.prefix = "/", SERVE_FILES("./static")},
        {.prefix = NULL},
    };

    lwan_set_url_map(&l, default_map);
    lwan_main_loop(&l);
    lwan_shutdown(&l);

    lwan_tpl_free(json_tpl.tpl);
    lwan_tpl_free(xml_tpl.tpl);
    lwan_tpl_free(csv_tpl.tpl);
#if QUERIES_PER_HOUR != 0
    cache_destroy(query_limit);
#endif
    cache_destroy(cache);
    sqlite3_close(db);

    return 0;
}