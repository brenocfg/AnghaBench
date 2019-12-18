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
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NLM_FAILED ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_nlm4_stat(struct xdr_stream *xdr,
			     const __be32 stat)
{
	__be32 *p;

	BUG_ON(be32_to_cpu(stat) > NLM_FAILED);
	p = xdr_reserve_space(xdr, 4);
	*p = stat;
}