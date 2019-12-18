#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t elements; scalar_t__ base; } ;
struct fortune_array {TYPE_2__ base; } ;
struct db_stmt {int dummy; } ;
struct TYPE_4__ {char* s; int /*<<< orphan*/  i; } ;
struct db_row {char kind; int buffer_length; TYPE_1__ u; } ;
struct coro {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  message; int /*<<< orphan*/  id; } ;
struct Fortune {TYPE_3__ item; } ;
typedef  int /*<<< orphan*/  fortune_query ;
typedef  int /*<<< orphan*/  fortune_buffer ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  append_fortune (struct coro*,struct fortune_array*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  coro_yield (struct coro*,int) ; 
 int /*<<< orphan*/  database ; 
 struct db_stmt* db_prepare_stmt (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  db_stmt_finalize (struct db_stmt*) ; 
 scalar_t__ db_stmt_step (struct db_stmt*,struct db_row*) ; 
 int /*<<< orphan*/  fortune_array_init (struct fortune_array*) ; 
 int /*<<< orphan*/  fortune_array_reset (struct fortune_array*) ; 
 int /*<<< orphan*/  fortune_array_sort (struct fortune_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fortune_compare ; 

__attribute__((used)) static int fortune_list_generator(struct coro *coro, void *data)
{
    static const char fortune_query[] = "SELECT * FROM Fortune";
    char fortune_buffer[256];
    struct Fortune *fortune = data;
    struct fortune_array fortunes;
    struct db_stmt *stmt;
    size_t i;

    stmt = db_prepare_stmt(database, fortune_query, sizeof(fortune_query) - 1);
    if (UNLIKELY(!stmt))
        return 0;

    fortune_array_init(&fortunes);

    struct db_row results[] = {
        { .kind = 'i' },
        { .kind = 's', .u.s = fortune_buffer, .buffer_length = sizeof(fortune_buffer) },
        { .kind = '\0' }
    };
    while (db_stmt_step(stmt, results)) {
        if (!append_fortune(coro, &fortunes, results[0].u.i, results[1].u.s))
            goto out;
    }

    if (!append_fortune(coro, &fortunes, 0,
                            "Additional fortune added at request time."))
        goto out;

    fortune_array_sort(&fortunes, fortune_compare);

    for (i = 0; i < fortunes.base.elements; i++) {
        struct Fortune *f = &((struct Fortune *)fortunes.base.base)[i];
        fortune->item.id = f->item.id;
        fortune->item.message = f->item.message;
        coro_yield(coro, 1);
    }

out:
    fortune_array_reset(&fortunes);
    db_stmt_finalize(stmt);
    return 0;
}