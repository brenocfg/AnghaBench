#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* data; } ;
struct web_client {TYPE_1__ response; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  contenttype; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  CT_TEXT_HTML ; 
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 int HTTP_RESP_BAD_REQUEST ; 
 int HTTP_RESP_NOT_FOUND ; 
 int /*<<< orphan*/  buffer_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  buffer_sprintf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  buffer_strcat_htmlescape (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 char* mystrsep (char**,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int web_client_api_request_v1 (int /*<<< orphan*/ *,struct web_client*,char*) ; 

int web_client_api_request(RRDHOST *host, struct web_client *w, char *url)
{
    // get the api version
    char *tok = mystrsep(&url, "/");
    if(tok && *tok) {
        debug(D_WEB_CLIENT, "%llu: Searching for API version '%s'.", w->id, tok);
        if(strcmp(tok, "v1") == 0)
            return web_client_api_request_v1(host, w, url);
        else {
            buffer_flush(w->response.data);
            w->response.data->contenttype = CT_TEXT_HTML;
            buffer_strcat(w->response.data, "Unsupported API version: ");
            buffer_strcat_htmlescape(w->response.data, tok);
            return HTTP_RESP_NOT_FOUND;
        }
    }
    else {
        buffer_flush(w->response.data);
        buffer_sprintf(w->response.data, "Which API version?");
        return HTTP_RESP_BAD_REQUEST;
    }
}