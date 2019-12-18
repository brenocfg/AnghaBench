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
typedef  scalar_t__ __be16 ;

/* Variables and functions */

__attribute__((used)) static int __sctp_auth_find_hmacid(__be16 *hmacs, int n_elts, __be16 hmac_id)
{
	int  found = 0;
	int  i;

	for (i = 0; i < n_elts; i++) {
		if (hmac_id == hmacs[i]) {
			found = 1;
			break;
		}
	}

	return found;
}