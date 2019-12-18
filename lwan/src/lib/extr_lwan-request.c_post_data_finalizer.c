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
struct lwan_request_parser_helper {scalar_t__ error_when_time; int error_when_n_packets; } ;
struct lwan_request {struct lwan_request_parser_helper* helper; } ;
typedef  enum lwan_read_finalizer { ____Placeholder_lwan_read_finalizer } lwan_read_finalizer ;

/* Variables and functions */
 int FINALIZER_DONE ; 
 int FINALIZER_ERROR_TIMEOUT ; 
 int FINALIZER_TRY_AGAIN ; 
 scalar_t__ UNLIKELY (int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum lwan_read_finalizer
post_data_finalizer(size_t total_read,
                    size_t buffer_size,
                    struct lwan_request *request,
                    int n_packets)
{
    struct lwan_request_parser_helper *helper = request->helper;

    if (buffer_size == total_read)
        return FINALIZER_DONE;

    /* For POST requests, the body can be larger, and due to small MTUs on
     * most ethernet connections, responding with a timeout solely based on
     * number of packets doesn't work.  Use keepalive timeout instead.  */
    if (UNLIKELY(time(NULL) > helper->error_when_time))
        return FINALIZER_ERROR_TIMEOUT;

    /* In addition to time, also estimate the number of packets based on an
     * usual MTU value and the request body size.  */
    if (UNLIKELY(n_packets > helper->error_when_n_packets))
        return FINALIZER_ERROR_TIMEOUT;

    return FINALIZER_TRY_AGAIN;
}