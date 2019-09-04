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
struct rds_header {int /*<<< orphan*/  h_csum; } ;

/* Variables and functions */
 scalar_t__ ip_fast_csum (void*,int) ; 

__attribute__((used)) static inline int rds_message_verify_checksum(const struct rds_header *hdr)
{
	return !hdr->h_csum || ip_fast_csum((void *) hdr, sizeof(*hdr) >> 2) == 0;
}