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
struct lwan_response {char* mime_type; int /*<<< orphan*/  buffer; } ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;
typedef  int /*<<< orphan*/  JsonNode ;

/* Variables and functions */
 int HTTP_INTERNAL_ERROR ; 
 int HTTP_OK ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_delete (int /*<<< orphan*/ *) ; 
 char* json_stringify_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  lwan_strbuf_set (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static enum lwan_http_status
json_response(struct lwan_response *response, JsonNode *node)
{
    size_t length;
    char *serialized;

    serialized = json_stringify_length(node, NULL, &length);
    json_delete(node);
    if (UNLIKELY(!serialized))
        return HTTP_INTERNAL_ERROR;

    lwan_strbuf_set(response->buffer, serialized, length);
    free(serialized);

    response->mime_type = "application/json";
    return HTTP_OK;
}