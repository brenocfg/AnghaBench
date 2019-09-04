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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_BYTES_SPECIAL_SEG ; 
 int /*<<< orphan*/ * xdr_check_write_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static __be32 *xdr_check_reply_chunk(__be32 *p, const __be32 *end)
{
	if (*p++ != xdr_zero) {
		p = xdr_check_write_chunk(p, end, MAX_BYTES_SPECIAL_SEG);
		if (!p)
			return NULL;
	}
	return p;
}