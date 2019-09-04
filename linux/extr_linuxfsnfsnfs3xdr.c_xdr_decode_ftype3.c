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
typedef  int /*<<< orphan*/  umode_t ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 size_t NF3FIFO ; 
 size_t NF3NON ; 
 size_t be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs_type2fmt ; 

__attribute__((used)) static __be32 *xdr_decode_ftype3(__be32 *p, umode_t *mode)
{
	u32 type;

	type = be32_to_cpup(p++);
	if (type > NF3FIFO)
		type = NF3NON;
	*mode = nfs_type2fmt[type];
	return p;
}