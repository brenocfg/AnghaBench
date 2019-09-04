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
struct vc_data {struct uni_pagedir** vc_uni_pagedir_loc; } ;
struct uni_pagedir {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  con_free_unimap (struct vc_data*) ; 

int con_copy_unimap(struct vc_data *dst_vc, struct vc_data *src_vc)
{
	struct uni_pagedir *q;

	if (!*src_vc->vc_uni_pagedir_loc)
		return -EINVAL;
	if (*dst_vc->vc_uni_pagedir_loc == *src_vc->vc_uni_pagedir_loc)
		return 0;
	con_free_unimap(dst_vc);
	q = *src_vc->vc_uni_pagedir_loc;
	q->refcount++;
	*dst_vc->vc_uni_pagedir_loc = q;
	return 0;
}