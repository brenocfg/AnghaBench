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
typedef  int /*<<< orphan*/  u32 ;
struct qman_portal {int dummy; } ;
struct qman_fq {int dummy; } ;

/* Variables and functions */
 struct qman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 int set_p_vdqcr (struct qman_portal*,struct qman_fq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_vdqcr(struct qman_portal **p, struct qman_fq *fq, u32 vdqcr)
{
	int ret;

	*p = get_affine_portal();
	ret = set_p_vdqcr(*p, fq, vdqcr);
	put_affine_portal();
	return ret;
}