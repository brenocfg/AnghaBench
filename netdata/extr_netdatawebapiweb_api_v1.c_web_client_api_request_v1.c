#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct web_client {int acl; TYPE_1__ response; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {char* command; scalar_t__ hash; int acl; int (* callback ) (int /*<<< orphan*/ *,struct web_client*,char*) ;} ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 int WEB_CLIENT_ACL_NOCHECK ; 
 TYPE_2__* api_commands ; 
 int /*<<< orphan*/  buffer_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  buffer_strcat_htmlescape (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 char* mystrsep (char**,char*) ; 
 void* simple_hash (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int stub1 (int /*<<< orphan*/ *,struct web_client*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int web_client_permission_denied (struct web_client*) ; 

inline int web_client_api_request_v1(RRDHOST *host, struct web_client *w, char *url) {
    static int initialized = 0;
    int i;

    if(unlikely(initialized == 0)) {
        initialized = 1;

        for(i = 0; api_commands[i].command ; i++)
            api_commands[i].hash = simple_hash(api_commands[i].command);
    }

    // get the command
    char *tok = mystrsep(&url, "?");
    if(tok && *tok) {
        debug(D_WEB_CLIENT, "%llu: Searching for API v1 command '%s'.", w->id, tok);
        uint32_t hash = simple_hash(tok);

        for(i = 0; api_commands[i].command ;i++) {
            if(unlikely(hash == api_commands[i].hash && !strcmp(tok, api_commands[i].command))) {
                if(unlikely(api_commands[i].acl != WEB_CLIENT_ACL_NOCHECK) &&  !(w->acl & api_commands[i].acl))
                    return web_client_permission_denied(w);

                return api_commands[i].callback(host, w, url);
            }
        }

        buffer_flush(w->response.data);
        buffer_strcat(w->response.data, "Unsupported v1 API command: ");
        buffer_strcat_htmlescape(w->response.data, tok);
        return 404;
    }
    else {
        buffer_flush(w->response.data);
        buffer_sprintf(w->response.data, "Which API v1 command?");
        return 400;
    }
}