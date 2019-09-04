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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  const __be32 ;

/* Variables and functions */
 scalar_t__ MAX_BYTES_SPECIAL_SEG ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static __be32 *xdr_check_read_list(__be32 *p, const __be32 *end)
{
	u32 position;
	bool first;

	first = true;
	while (*p++ != xdr_zero) {
		if (first) {
			position = be32_to_cpup(p++);
			first = false;
		} else if (be32_to_cpup(p++) != position) {
			return NULL;
		}
		p++;	/* handle */
		if (be32_to_cpup(p++) > MAX_BYTES_SPECIAL_SEG)
			return NULL;
		p += 2;	/* offset */

		if (p > end)
			return NULL;
	}
	return p;
}