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
struct TYPE_6__ {unsigned int verbose; } ;

/* Variables and functions */
 unsigned int MAX_VERBOSITY_LEVEL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_noreply_maybe (int /*<<< orphan*/ *,TYPE_1__*,size_t const) ; 
 TYPE_2__ settings ; 
 unsigned int strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void process_verbosity_command(conn *c, token_t *tokens, const size_t ntokens) {
    unsigned int level;

    assert(c != NULL);

    set_noreply_maybe(c, tokens, ntokens);

    level = strtoul(tokens[1].value, NULL, 10);
    settings.verbose = level > MAX_VERBOSITY_LEVEL ? MAX_VERBOSITY_LEVEL : level;
    out_string(c, "OK");
    return;
}