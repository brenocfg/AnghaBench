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
struct web_client {int dummy; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */

__attribute__((used)) static inline int check_host_and_call(RRDHOST *host, struct web_client *w, char *url, int (*func)(RRDHOST *, struct web_client *, char *)) {
    //if(unlikely(host->rrd_memory_mode == RRD_MEMORY_MODE_NONE)) {
    //    buffer_flush(w->response.data);
    //    buffer_strcat(w->response.data, "This host does not maintain a database");
    //    return HTTP_RESP_BAD_REQUEST;
    //}

    return func(host, w, url);
}