#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_4__ {int /*<<< orphan*/  hostname; } ;
typedef  TYPE_1__ RRDHOST ;
typedef  int PROMETHEUS_OUTPUT_OPTIONS ;
typedef  int /*<<< orphan*/  BUFFER ;
typedef  int /*<<< orphan*/  BACKEND_OPTIONS ;

/* Variables and functions */
 scalar_t__ BACKEND_OPTIONS_DATA_SOURCE (int /*<<< orphan*/ ) ; 
 scalar_t__ BACKEND_SOURCE_DATA_AS_COLLECTED ; 
 scalar_t__ BACKEND_SOURCE_DATA_AVERAGE ; 
 scalar_t__ BACKEND_SOURCE_DATA_SUM ; 
 int PROMETHEUS_OUTPUT_HELP ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char const*,char*,unsigned long,char*,unsigned long,unsigned long) ; 
 scalar_t__ global_backend_update_every ; 
 scalar_t__ prometheus_server_last_access (char const*,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static inline time_t prometheus_preparation(RRDHOST *host, BUFFER *wb, BACKEND_OPTIONS backend_options, const char *server, time_t now, PROMETHEUS_OUTPUT_OPTIONS output_options) {
    if(!server || !*server) server = "default";

    time_t after  = prometheus_server_last_access(server, host, now);

    int first_seen = 0;
    if(!after) {
        after = now - global_backend_update_every;
        first_seen = 1;
    }

    if(after > now) {
        // oops! this should never happen
        after = now - global_backend_update_every;
    }

    if(output_options & PROMETHEUS_OUTPUT_HELP) {
        char *mode;
        if(BACKEND_OPTIONS_DATA_SOURCE(backend_options) == BACKEND_SOURCE_DATA_AS_COLLECTED)
            mode = "as collected";
        else if(BACKEND_OPTIONS_DATA_SOURCE(backend_options) == BACKEND_SOURCE_DATA_AVERAGE)
            mode = "average";
        else if(BACKEND_OPTIONS_DATA_SOURCE(backend_options) == BACKEND_SOURCE_DATA_SUM)
            mode = "sum";
        else
            mode = "unknown";

        buffer_sprintf(wb, "# COMMENT netdata \"%s\" to %sprometheus \"%s\", source \"%s\", last seen %lu %s, time range %lu to %lu\n\n"
                , host->hostname
                , (first_seen)?"FIRST SEEN ":""
                , server
                , mode
                , (unsigned long)((first_seen)?0:(now - after))
                , (first_seen)?"never":"seconds ago"
                , (unsigned long)after, (unsigned long)now
        );
    }

    return after;
}