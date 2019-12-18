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
typedef  int xfs_km_flags_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int KM_NOFS ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 void* __vmalloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_flags_convert (int) ; 
 int /*<<< orphan*/  memalloc_nofs_restore (unsigned int) ; 
 unsigned int memalloc_nofs_save () ; 

__attribute__((used)) static void *
__kmem_vmalloc(size_t size, xfs_km_flags_t flags)
{
	unsigned nofs_flag = 0;
	void	*ptr;
	gfp_t	lflags = kmem_flags_convert(flags);

	if (flags & KM_NOFS)
		nofs_flag = memalloc_nofs_save();

	ptr = __vmalloc(size, lflags, PAGE_KERNEL);

	if (flags & KM_NOFS)
		memalloc_nofs_restore(nofs_flag);

	return ptr;
}