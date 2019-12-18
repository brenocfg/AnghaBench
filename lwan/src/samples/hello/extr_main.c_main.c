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
struct lwan_url_map {char* prefix; int /*<<< orphan*/  handler; } ;
struct lwan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWAN_HANDLER_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hello_world ; 
 int /*<<< orphan*/  lwan_init (struct lwan*) ; 
 int /*<<< orphan*/  lwan_main_loop (struct lwan*) ; 
 int /*<<< orphan*/  lwan_set_url_map (struct lwan*,struct lwan_url_map const*) ; 
 int /*<<< orphan*/  lwan_shutdown (struct lwan*) ; 

int
main(void)
{
    const struct lwan_url_map default_map[] = {
        { .prefix = "/", .handler = LWAN_HANDLER_REF(hello_world) },
        { .prefix = NULL }
    };
    struct lwan l;

    lwan_init(&l);

    lwan_set_url_map(&l, default_map);
    lwan_main_loop(&l);

    lwan_shutdown(&l);

    return 0;
}