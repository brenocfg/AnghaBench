#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  conn ;
struct TYPE_6__ {double slab_automove_ratio; unsigned int slab_automove; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  safe_strtod (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  set_noreply_maybe (int /*<<< orphan*/ *,TYPE_1__*,size_t const) ; 
 TYPE_2__ settings ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 unsigned int strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void process_slabs_automove_command(conn *c, token_t *tokens, const size_t ntokens) {
    unsigned int level;
    double ratio;

    assert(c != NULL);

    set_noreply_maybe(c, tokens, ntokens);

    if (strcmp(tokens[2].value, "ratio") == 0) {
        if (ntokens < 5 || !safe_strtod(tokens[3].value, &ratio)) {
            out_string(c, "ERROR");
            return;
        }
        settings.slab_automove_ratio = ratio;
    } else {
        level = strtoul(tokens[2].value, NULL, 10);
        if (level == 0) {
            settings.slab_automove = 0;
        } else if (level == 1 || level == 2) {
            settings.slab_automove = level;
        } else {
            out_string(c, "ERROR");
            return;
        }
    }
    out_string(c, "OK");
    return;
}