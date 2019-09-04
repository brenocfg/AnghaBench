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
struct sw842_param {void** index2; void** index4; void** index8; } ;

/* Variables and functions */
 void* INDEX_NOT_CHECKED ; 
 int OPS_MAX ; 
 int add_template (struct sw842_param*,int) ; 
 scalar_t__ check_template (struct sw842_param*,int) ; 

__attribute__((used)) static int process_next(struct sw842_param *p)
{
	int ret, i;

	p->index8[0] = INDEX_NOT_CHECKED;
	p->index4[0] = INDEX_NOT_CHECKED;
	p->index4[1] = INDEX_NOT_CHECKED;
	p->index2[0] = INDEX_NOT_CHECKED;
	p->index2[1] = INDEX_NOT_CHECKED;
	p->index2[2] = INDEX_NOT_CHECKED;
	p->index2[3] = INDEX_NOT_CHECKED;

	/* check up to OPS_MAX - 1; last op is our fallback */
	for (i = 0; i < OPS_MAX - 1; i++) {
		if (check_template(p, i))
			break;
	}

	ret = add_template(p, i);
	if (ret)
		return ret;

	return 0;
}