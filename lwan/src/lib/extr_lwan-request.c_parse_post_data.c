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
struct TYPE_2__ {int len; int /*<<< orphan*/  value; } ;
struct lwan_request_parser_helper {int /*<<< orphan*/  post_params; int /*<<< orphan*/  post_data; TYPE_1__ content_type; } ;
struct lwan_request {struct lwan_request_parser_helper* helper; } ;
typedef  int /*<<< orphan*/  content_type ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_key_values (struct lwan_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  url_decode ; 

__attribute__((used)) static void parse_post_data(struct lwan_request *request)
{
    struct lwan_request_parser_helper *helper = request->helper;
    static const char content_type[] = "application/x-www-form-urlencoded";

    if (helper->content_type.len < sizeof(content_type) - 1)
        return;
    if (UNLIKELY(strncmp(helper->content_type.value, content_type,
                         sizeof(content_type) - 1)))
        return;

    parse_key_values(request, &helper->post_data, &helper->post_params,
                     url_decode, '&');
}