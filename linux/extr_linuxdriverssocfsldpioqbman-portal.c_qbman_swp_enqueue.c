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
struct qbman_swp {int dummy; } ;
struct dpaa2_fd {int dummy; } ;
struct qbman_eq_desc {int verb; struct dpaa2_fd const fd; struct dpaa2_fd const dca; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EQAR_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EQAR_SUCCESS (int /*<<< orphan*/ ) ; 
 int EQAR_VB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QBMAN_CENA_SWP_EQCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QBMAN_CINH_SWP_EQAR ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  memcpy (struct dpaa2_fd const*,struct dpaa2_fd const*,int) ; 
 struct qbman_eq_desc* qbman_get_cmd (struct qbman_swp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qbman_read_register (struct qbman_swp*,int /*<<< orphan*/ ) ; 

int qbman_swp_enqueue(struct qbman_swp *s, const struct qbman_eq_desc *d,
		      const struct dpaa2_fd *fd)
{
	struct qbman_eq_desc *p;
	u32 eqar = qbman_read_register(s, QBMAN_CINH_SWP_EQAR);

	if (!EQAR_SUCCESS(eqar))
		return -EBUSY;

	p = qbman_get_cmd(s, QBMAN_CENA_SWP_EQCR(EQAR_IDX(eqar)));
	memcpy(&p->dca, &d->dca, 31);
	memcpy(&p->fd, fd, sizeof(*fd));

	/* Set the verb byte, have to substitute in the valid-bit */
	dma_wmb();
	p->verb = d->verb | EQAR_VB(eqar);

	return 0;
}