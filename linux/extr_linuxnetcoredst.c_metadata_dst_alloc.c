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
typedef  scalar_t__ u8 ;
struct metadata_dst {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum metadata_type { ____Placeholder_metadata_type } metadata_type ;

/* Variables and functions */
 int /*<<< orphan*/  __metadata_dst_init (struct metadata_dst*,int,scalar_t__) ; 
 struct metadata_dst* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

struct metadata_dst *metadata_dst_alloc(u8 optslen, enum metadata_type type,
					gfp_t flags)
{
	struct metadata_dst *md_dst;

	md_dst = kmalloc(sizeof(*md_dst) + optslen, flags);
	if (!md_dst)
		return NULL;

	__metadata_dst_init(md_dst, type, optslen);

	return md_dst;
}