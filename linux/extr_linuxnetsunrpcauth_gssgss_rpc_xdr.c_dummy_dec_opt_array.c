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
struct xdr_stream {int dummy; } ;
struct gssx_option_array {int /*<<< orphan*/ * data; scalar_t__ count; } ;
struct gssx_option {int dummy; } ;
typedef  int /*<<< orphan*/  dummy ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gssx_dec_option (struct xdr_stream*,struct gssx_option*) ; 
 int /*<<< orphan*/  memset (struct gssx_option*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int dummy_dec_opt_array(struct xdr_stream *xdr,
				struct gssx_option_array *oa)
{
	struct gssx_option dummy;
	u32 count, i;
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(p == NULL))
		return -ENOSPC;
	count = be32_to_cpup(p++);
	memset(&dummy, 0, sizeof(dummy));
	for (i = 0; i < count; i++) {
		gssx_dec_option(xdr, &dummy);
	}

	oa->count = 0;
	oa->data = NULL;
	return 0;
}