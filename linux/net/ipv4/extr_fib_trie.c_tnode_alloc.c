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
struct tnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 size_t TNODE_SIZE (unsigned long) ; 
 int TNODE_VMALLOC_MAX ; 
 struct tnode* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 struct tnode* vzalloc (size_t) ; 

__attribute__((used)) static struct tnode *tnode_alloc(int bits)
{
	size_t size;

	/* verify bits is within bounds */
	if (bits > TNODE_VMALLOC_MAX)
		return NULL;

	/* determine size and verify it is non-zero and didn't overflow */
	size = TNODE_SIZE(1ul << bits);

	if (size <= PAGE_SIZE)
		return kzalloc(size, GFP_KERNEL);
	else
		return vzalloc(size);
}