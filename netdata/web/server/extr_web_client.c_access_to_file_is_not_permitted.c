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

/* Variables and functions */
 int /*<<< orphan*/  CT_TEXT_HTML ; 
 int HTTP_RESP_FORBIDDEN ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  buffer_strcat_htmlescape (TYPE_2__*,char const*) ; 

__attribute__((used)) static inline int access_to_file_is_not_permitted(struct web_client *w, const char *filename) {
    w->response.data->contenttype = CT_TEXT_HTML;
    buffer_strcat(w->response.data, "Access to file is not permitted: ");
    buffer_strcat_htmlescape(w->response.data, filename);
    return HTTP_RESP_FORBIDDEN;
}