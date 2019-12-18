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
struct lwan_request {int dummy; } ;
typedef  int /*<<< orphan*/  message ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;

/* Variables and functions */
 int HTTP_OK ; 
 int /*<<< orphan*/  lwan_strbuf_set_static (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static enum lwan_http_status hello_world(struct lwan_request *request
                                         __attribute__((unused)),
                                         struct lwan_response *response,
                                         void *data __attribute__((unused)))
{
    static const char message[] = "Hello, World!";

    response->mime_type = "text/plain";
    lwan_strbuf_set_static(response->buffer, message, sizeof(message) - 1);

    return HTTP_OK;
}