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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_inval ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 *decode_array_32_alloc(void **p, void *end, u32 *plen)
{
	u32 *a = NULL;
	u32 len;
	int ret;

	ceph_decode_32_safe(p, end, len, e_inval);
	if (len) {
		u32 i;

		a = kmalloc_array(len, sizeof(u32), GFP_NOIO);
		if (!a) {
			ret = -ENOMEM;
			goto fail;
		}

		ceph_decode_need(p, end, len * sizeof(u32), e_inval);
		for (i = 0; i < len; i++)
			a[i] = ceph_decode_32(p);
	}

	*plen = len;
	return a;

e_inval:
	ret = -EINVAL;
fail:
	kfree(a);
	return ERR_PTR(ret);
}