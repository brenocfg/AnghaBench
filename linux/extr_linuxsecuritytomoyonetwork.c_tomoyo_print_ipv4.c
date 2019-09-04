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
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,unsigned int const,char*,scalar_t__ const*,char,scalar_t__ const*) ; 

__attribute__((used)) static void tomoyo_print_ipv4(char *buffer, const unsigned int buffer_len,
			      const __be32 *min_ip, const __be32 *max_ip)
{
	snprintf(buffer, buffer_len, "%pI4%c%pI4", min_ip,
		 *min_ip == *max_ip ? '\0' : '-', max_ip);
}