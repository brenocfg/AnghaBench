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
struct lwan_request {int flags; } ;
typedef  enum lwan_request_flags { ____Placeholder_lwan_request_flags } lwan_request_flags ;

/* Variables and functions */
 int REQUEST_METHOD_MASK ; 

__attribute__((used)) static inline enum lwan_request_flags
lwan_request_get_method(const struct lwan_request *request)
{
    return (enum lwan_request_flags)(request->flags & REQUEST_METHOD_MASK);
}