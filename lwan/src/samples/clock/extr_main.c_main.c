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
struct lwan_url_map {char* prefix; int /*<<< orphan*/  member_1; struct index* data; int /*<<< orphan*/  handler; } ;
struct lwan {int dummy; } ;
struct index {char* title; char* variant; int width; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWAN_HANDLER_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REDIRECT (char*) ; 
 int /*<<< orphan*/  blocks ; 
 int /*<<< orphan*/  clock ; 
 int /*<<< orphan*/  dali ; 
 int /*<<< orphan*/  lwan_init (struct lwan*) ; 
 int /*<<< orphan*/  lwan_main_loop (struct lwan*) ; 
 int /*<<< orphan*/  lwan_set_url_map (struct lwan*,struct lwan_url_map const*) ; 
 int /*<<< orphan*/  lwan_shutdown (struct lwan*) ; 
 int /*<<< orphan*/  templated_index ; 

int main(void)
{
    struct index sample_clock = {
        .title = "Lwan Sample Clock",
        .variant = "clock",
        .width = 200,
    };
    struct index dali_clock = {
        .title = "Lwan Dali Clock",
        .variant = "dali",
        .width = 320,
    };
    struct index blocks_clock = {
        .title = "Lwan Blocks Clock",
        .variant = "blocks",
        .width = 320,
    };
    const struct lwan_url_map default_map[] = {
        {
            .prefix = "/clock.gif",
            .handler = LWAN_HANDLER_REF(clock),
        },
        {
            .prefix = "/dali.gif",
            .handler = LWAN_HANDLER_REF(dali),
        },
        {
            .prefix = "/blocks.gif",
            .handler = LWAN_HANDLER_REF(blocks),
        },
        {
            .prefix = "/clock",
            .handler = LWAN_HANDLER_REF(templated_index),
            .data = &sample_clock,
        },
        {
            .prefix = "/dali",
            .handler = LWAN_HANDLER_REF(templated_index),
            .data = &dali_clock,
        },
        {
            .prefix = "/blocks",
            .handler = LWAN_HANDLER_REF(templated_index),
            .data = &blocks_clock,
        },
        {
            .prefix = "/",
            REDIRECT("/clock"),
        },
        {},
    };
    struct lwan l;

    lwan_init(&l);

    lwan_set_url_map(&l, default_map);
    lwan_main_loop(&l);

    lwan_shutdown(&l);

    return 0;
}