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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NF2FIFO ; 
 scalar_t__ NFBAD ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static __be32 *xdr_decode_ftype(__be32 *p, u32 *type)
{
	*type = be32_to_cpup(p++);
	if (unlikely(*type > NF2FIFO))
		*type = NFBAD;
	return p;
}