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
typedef  int /*<<< orphan*/  conn ;
struct TYPE_2__ {int detail_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_string (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ settings ; 
 char* stats_prefix_dump (int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  write_and_free (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) inline static void process_stats_detail(conn *c, const char *command) {
    assert(c != NULL);

    if (strcmp(command, "on") == 0) {
        settings.detail_enabled = 1;
        out_string(c, "OK");
    }
    else if (strcmp(command, "off") == 0) {
        settings.detail_enabled = 0;
        out_string(c, "OK");
    }
    else if (strcmp(command, "dump") == 0) {
        int len;
        char *stats = stats_prefix_dump(&len);
        write_and_free(c, stats, len);
    }
    else {
        out_string(c, "CLIENT_ERROR usage: stats detail on|off|dump");
    }
}