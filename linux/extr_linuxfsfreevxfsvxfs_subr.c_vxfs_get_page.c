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
typedef  int /*<<< orphan*/  u_long ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 struct page* read_mapping_page (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxfs_put_page (struct page*) ; 

struct page *
vxfs_get_page(struct address_space *mapping, u_long n)
{
	struct page *			pp;

	pp = read_mapping_page(mapping, n, NULL);

	if (!IS_ERR(pp)) {
		kmap(pp);
		/** if (!PageChecked(pp)) **/
			/** vxfs_check_page(pp); **/
		if (PageError(pp))
			goto fail;
	}
	
	return (pp);
		 
fail:
	vxfs_put_page(pp);
	return ERR_PTR(-EIO);
}