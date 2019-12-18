#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {size_t const len; int /*<<< orphan*/  value; } ;
struct TYPE_4__ {int /*<<< orphan*/  parsed; TYPE_1__ raw; } ;
struct lwan_request_parser_helper {TYPE_2__ if_modified_since; } ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 scalar_t__ lwan_parse_rfc_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void parse_if_modified_since(struct lwan_request_parser_helper *helper)
{
    static const size_t header_len =
        sizeof("Wed, 17 Apr 2019 13:59:27 GMT") - 1;
    time_t parsed;

    if (UNLIKELY(helper->if_modified_since.raw.len != header_len))
        return;

    if (UNLIKELY(lwan_parse_rfc_time(helper->if_modified_since.raw.value,
                                     &parsed) < 0))
        return;

    helper->if_modified_since.parsed = parsed;
}