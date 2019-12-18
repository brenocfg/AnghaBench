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
struct TYPE_3__ {struct lwan_key_value* headers; } ;
struct lwan_request {TYPE_1__ response; TYPE_2__* conn; } ;
struct lwan_key_value {char* key; int /*<<< orphan*/ * value; } ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;
struct TYPE_4__ {int /*<<< orphan*/  coro; } ;

/* Variables and functions */
 int HTTP_INTERNAL_ERROR ; 
 int HTTP_MOVED_PERMANENTLY ; 
 scalar_t__ UNLIKELY (int) ; 
 struct lwan_key_value* coro_malloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * coro_strdup (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static enum lwan_http_status module_redirect_to(struct lwan_request *request,
                                                const char *url)
{
    struct lwan_key_value *headers =
        coro_malloc(request->conn->coro, sizeof(*headers) * 2);

    if (UNLIKELY(!headers))
        return HTTP_INTERNAL_ERROR;

    headers[0].key = "Location";
    headers[0].value = coro_strdup(request->conn->coro, url);
    if (UNLIKELY(!headers[0].value))
        return HTTP_INTERNAL_ERROR;

    headers[1].key = NULL;
    headers[1].value = NULL;
    request->response.headers = headers;

    return HTTP_MOVED_PERMANENTLY;
}