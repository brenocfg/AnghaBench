#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct subchannel_id {scalar_t__ sch_no; } ;
struct qdio_ssqd_desc {int dummy; } ;
struct qdio_irq {scalar_t__ chsc_page; } ;
struct TYPE_2__ {int flags; scalar_t__ sch; } ;
struct chsc_ssqd_area {TYPE_1__ qdio_ssqd; } ;

/* Variables and functions */
 int CHSC_FLAG_QDIO_CAPABILITY ; 
 int CHSC_FLAG_VALIDITY ; 
 int /*<<< orphan*/  DBF_EVENT (char*,scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int chsc_ssqd (struct subchannel_id,struct chsc_ssqd_area*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  memcpy (struct qdio_ssqd_desc*,TYPE_1__*,int) ; 

int qdio_setup_get_ssqd(struct qdio_irq *irq_ptr,
			struct subchannel_id *schid,
			struct qdio_ssqd_desc *data)
{
	struct chsc_ssqd_area *ssqd;
	int rc;

	DBF_EVENT("getssqd:%4x", schid->sch_no);
	if (!irq_ptr) {
		ssqd = (struct chsc_ssqd_area *)__get_free_page(GFP_KERNEL);
		if (!ssqd)
			return -ENOMEM;
	} else {
		ssqd = (struct chsc_ssqd_area *)irq_ptr->chsc_page;
	}

	rc = chsc_ssqd(*schid, ssqd);
	if (rc)
		goto out;

	if (!(ssqd->qdio_ssqd.flags & CHSC_FLAG_QDIO_CAPABILITY) ||
	    !(ssqd->qdio_ssqd.flags & CHSC_FLAG_VALIDITY) ||
	    (ssqd->qdio_ssqd.sch != schid->sch_no))
		rc = -EINVAL;

	if (!rc)
		memcpy(data, &ssqd->qdio_ssqd, sizeof(*data));

out:
	if (!irq_ptr)
		free_page((unsigned long)ssqd);

	return rc;
}