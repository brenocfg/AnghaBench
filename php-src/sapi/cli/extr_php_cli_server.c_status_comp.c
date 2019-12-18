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
struct TYPE_2__ {scalar_t__ code; } ;
typedef  TYPE_1__ http_response_status_code_pair ;

/* Variables and functions */

__attribute__((used)) static int status_comp(const void *a, const void *b) /* {{{ */
{
	const http_response_status_code_pair *pa = (const http_response_status_code_pair *) a;
	const http_response_status_code_pair *pb = (const http_response_status_code_pair *) b;

	if (pa->code < pb->code) {
		return -1;
	} else if (pa->code > pb->code) {
		return 1;
	}

	return 0;
}