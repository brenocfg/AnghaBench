#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* data; } ;
struct web_client {TYPE_1__ response; } ;
struct TYPE_5__ {int /*<<< orphan*/  contenttype; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  CT_APPLICATION_JSON ; 
 int /*<<< orphan*/  buffer_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  charts2json (int /*<<< orphan*/ *,TYPE_2__*) ; 

inline int web_client_api_request_v1_charts(RRDHOST *host, struct web_client *w, char *url) {
    (void)url;

    buffer_flush(w->response.data);
    w->response.data->contenttype = CT_APPLICATION_JSON;
    charts2json(host, w->response.data);
    return 200;
}