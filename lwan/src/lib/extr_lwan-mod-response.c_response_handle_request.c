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
struct lwan_response {int dummy; } ;
struct lwan_request {int dummy; } ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;

/* Variables and functions */

__attribute__((used)) static enum lwan_http_status
response_handle_request(struct lwan_request *request __attribute__((unused)),
                        struct lwan_response *response __attribute__((unused)),
                        void *instance)
{
    return (enum lwan_http_status)instance;
}