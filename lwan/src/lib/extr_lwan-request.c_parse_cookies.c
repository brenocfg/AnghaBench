#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lwan_value {char* value; int /*<<< orphan*/  len; } ;
struct lwan_request {TYPE_1__* helper; } ;
struct TYPE_2__ {int /*<<< orphan*/  cookies; } ;

/* Variables and functions */
 int /*<<< orphan*/  identity_decode ; 
 char* lwan_request_get_header (struct lwan_request*,char*) ; 
 int /*<<< orphan*/  parse_key_values (struct lwan_request*,struct lwan_value*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void parse_cookies(struct lwan_request *request)
{
    const char *cookies = lwan_request_get_header(request, "Cookie");

    if (!cookies)
        return;

    struct lwan_value header = {.value = (char *)cookies,
                                .len = strlen(cookies)};
    parse_key_values(request, &header, &request->helper->cookies,
                     identity_decode, ';');
}