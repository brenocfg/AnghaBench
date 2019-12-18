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
struct lwan_request_parser_helper {int /*<<< orphan*/  query_params; int /*<<< orphan*/  query_string; } ;
struct lwan_request {struct lwan_request_parser_helper* helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  parse_key_values (struct lwan_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  url_decode ; 

__attribute__((used)) static void parse_query_string(struct lwan_request *request)
{
    struct lwan_request_parser_helper *helper = request->helper;

    parse_key_values(request, &helper->query_string, &helper->query_params,
                     url_decode, '&');
}