#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lwan_value {char* value; size_t len; } ;
struct TYPE_12__ {char* value; size_t len; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
struct lwan_request_parser_helper {char* next_request; int /*<<< orphan*/  error_when_n_packets; scalar_t__ error_when_time; TYPE_6__ post_data; TYPE_4__* buffer; TYPE_3__ content_length; } ;
struct lwan_request {TYPE_5__* conn; struct lwan_request_parser_helper* helper; } ;
struct lwan_config {size_t max_post_data_size; scalar_t__ keep_alive_timeout; int /*<<< orphan*/  allow_post_temp_file; } ;
typedef  scalar_t__ ptrdiff_t ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;
struct TYPE_11__ {int /*<<< orphan*/  coro; TYPE_2__* thread; } ;
struct TYPE_10__ {char* value; int len; } ;
struct TYPE_8__ {TYPE_1__* lwan; } ;
struct TYPE_7__ {struct lwan_config config; } ;

/* Variables and functions */
 int HTTP_BAD_REQUEST ; 
 int HTTP_INTERNAL_ERROR ; 
 int HTTP_OK ; 
 int HTTP_TOO_LARGE ; 
 scalar_t__ UNLIKELY (int) ; 
 char* alloc_post_buffer (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_n_packets (size_t) ; 
 char* mempcpy (char*,char*,size_t) ; 
 long parse_long (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  post_data_finalizer ; 
 int read_from_request_socket (struct lwan_request*,struct lwan_value*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum lwan_http_status read_post_data(struct lwan_request *request)
{
    struct lwan_request_parser_helper *helper = request->helper;
    /* Holy indirection, Batman! */
    struct lwan_config *config = &request->conn->thread->lwan->config;
    const size_t max_post_data_size = config->max_post_data_size;
    char *new_buffer;
    long parsed_size;

    if (UNLIKELY(!helper->content_length.value))
        return HTTP_BAD_REQUEST;
    parsed_size = parse_long(helper->content_length.value, -1);
    if (UNLIKELY(parsed_size < 0))
        return HTTP_BAD_REQUEST;
    if (UNLIKELY(parsed_size >= (long)max_post_data_size))
        return HTTP_TOO_LARGE;

    size_t post_data_size = (size_t)parsed_size;
    size_t have;
    if (!helper->next_request) {
        have = 0;
    } else {
        char *buffer_end = helper->buffer->value + helper->buffer->len;
        have = (size_t)(ptrdiff_t)(buffer_end - helper->next_request);

        if (have >= post_data_size) {
            helper->post_data.value = helper->next_request;
            helper->post_data.len = post_data_size;
            helper->next_request += post_data_size;
            return HTTP_OK;
        }
    }

    new_buffer = alloc_post_buffer(request->conn->coro, post_data_size + 1,
                                   config->allow_post_temp_file);
    if (UNLIKELY(!new_buffer))
        return HTTP_INTERNAL_ERROR;

    helper->post_data.value = new_buffer;
    helper->post_data.len = post_data_size;
    if (have) {
        new_buffer = mempcpy(new_buffer, helper->next_request, have);
        post_data_size -= have;
    }
    helper->next_request = NULL;

    helper->error_when_time = time(NULL) + config->keep_alive_timeout;
    helper->error_when_n_packets = calculate_n_packets(post_data_size);

    struct lwan_value buffer = {.value = new_buffer,
                                .len = post_data_size};
    return read_from_request_socket(request, &buffer, buffer.len,
                                    post_data_finalizer);
}