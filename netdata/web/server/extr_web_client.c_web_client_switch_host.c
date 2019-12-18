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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {TYPE_2__* data; } ;
struct web_client {char* last_url; TYPE_1__ response; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  contenttype; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  CT_TEXT_HTML ; 
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 int HTTP_RESP_BAD_REQUEST ; 
 int HTTP_RESP_NOT_FOUND ; 
 scalar_t__ NETDATA_WEB_REQUEST_URL_SIZE ; 
 int /*<<< orphan*/  buffer_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  buffer_strcat_htmlescape (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * localhost ; 
 char* mystrsep (char**,char*) ; 
 int /*<<< orphan*/ * rrdhost_find_by_guid (char*,scalar_t__) ; 
 int /*<<< orphan*/ * rrdhost_find_by_hostname (char*,scalar_t__) ; 
 scalar_t__ simple_hash (char*) ; 
 int /*<<< orphan*/  strncpyz (char*,char*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int web_client_process_url (int /*<<< orphan*/ *,struct web_client*,char*) ; 

__attribute__((used)) static inline int web_client_switch_host(RRDHOST *host, struct web_client *w, char *url) {
    static uint32_t hash_localhost = 0;

    if(unlikely(!hash_localhost)) {
        hash_localhost = simple_hash("localhost");
    }

    if(host != localhost) {
        buffer_flush(w->response.data);
        buffer_strcat(w->response.data, "Nesting of hosts is not allowed.");
        return HTTP_RESP_BAD_REQUEST;
    }

    char *tok = mystrsep(&url, "/");
    if(tok && *tok) {
        debug(D_WEB_CLIENT, "%llu: Searching for host with name '%s'.", w->id, tok);

        // copy the URL, we need it to serve files
        w->last_url[0] = '/';
        if(url && *url) strncpyz(&w->last_url[1], url, NETDATA_WEB_REQUEST_URL_SIZE - 1);
        else w->last_url[1] = '\0';

        uint32_t hash = simple_hash(tok);

        host = rrdhost_find_by_hostname(tok, hash);
        if(!host) host = rrdhost_find_by_guid(tok, hash);

        if(host) return web_client_process_url(host, w, url);
    }

    buffer_flush(w->response.data);
    w->response.data->contenttype = CT_TEXT_HTML;
    buffer_strcat(w->response.data, "This netdata does not maintain a database for host: ");
    buffer_strcat_htmlescape(w->response.data, tok?tok:"");
    return HTTP_RESP_NOT_FOUND;
}