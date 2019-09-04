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
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  conn ;
struct TYPE_6__ {scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  out_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  safe_strtoul (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_noreply_maybe (int /*<<< orphan*/ *,TYPE_1__*,size_t const) ; 
 TYPE_2__ settings ; 
 scalar_t__ slabs_adjust_mem_limit (size_t) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void process_memlimit_command(conn *c, token_t *tokens, const size_t ntokens) {
    uint32_t memlimit;
    assert(c != NULL);

    set_noreply_maybe(c, tokens, ntokens);

    if (!safe_strtoul(tokens[1].value, &memlimit)) {
        out_string(c, "ERROR");
    } else {
        if (memlimit < 8) {
            out_string(c, "MEMLIMIT_TOO_SMALL cannot set maxbytes to less than 8m");
        } else {
            if (memlimit > 1000000000) {
                out_string(c, "MEMLIMIT_ADJUST_FAILED input value is megabytes not bytes");
            } else if (slabs_adjust_mem_limit((size_t) memlimit * 1024 * 1024)) {
                if (settings.verbose > 0) {
                    fprintf(stderr, "maxbytes adjusted to %llum\n", (unsigned long long)memlimit);
                }

                out_string(c, "OK");
            } else {
                out_string(c, "MEMLIMIT_ADJUST_FAILED out of bounds or unable to adjust");
            }
        }
    }
}