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
struct redir_cache_data {int /*<<< orphan*/  redir_to; } ;
struct lwan_request {int dummy; } ;
struct lwan_key_value {char* key; int /*<<< orphan*/  value; } ;
struct file_cache_entry {struct redir_cache_data redir_cache_data; } ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_MOVED_PERMANENTLY ; 
 int serve_buffer (struct lwan_request*,struct file_cache_entry*,struct lwan_key_value const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum lwan_http_status redir_serve(struct lwan_request *request,
                                         void *data)
{
    struct file_cache_entry *fce = data;
    struct redir_cache_data *rd = &fce->redir_cache_data;
    const struct lwan_key_value headers = {.key = "Location",
                                           .value = rd->redir_to};

    return serve_buffer(request, fce, &headers, rd->redir_to,
                        strlen(rd->redir_to), HTTP_MOVED_PERMANENTLY);
}