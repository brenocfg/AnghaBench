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
struct sctp_association {int /*<<< orphan*/ * strreset_result; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

__attribute__((used)) static void sctp_update_strreset_result(struct sctp_association *asoc,
					__u32 result)
{
	asoc->strreset_result[1] = asoc->strreset_result[0];
	asoc->strreset_result[0] = result;
}