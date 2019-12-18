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
typedef  enum lwan_request_flags { ____Placeholder_lwan_request_flags } lwan_request_flags ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;

/* Variables and functions */
 int HTTP_NOT_MODIFIED ; 

__attribute__((used)) static inline bool has_response_body(enum lwan_request_flags method,
                                     enum lwan_http_status status)
{
    /* See FOR_EACH_REQUEST_METHOD() in lwan.h */
    return (method & 1 << 0) || status != HTTP_NOT_MODIFIED;
}