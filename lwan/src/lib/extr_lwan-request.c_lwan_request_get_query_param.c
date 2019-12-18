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
struct lwan_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lwan_request_get_query_params (struct lwan_request*) ; 
 char const* value_lookup (int /*<<< orphan*/ ,char const*) ; 

const char *lwan_request_get_query_param(struct lwan_request *request,
                                         const char *key)
{
    return value_lookup(lwan_request_get_query_params(request), key);
}