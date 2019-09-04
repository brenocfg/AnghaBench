#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int genbit; } ;
struct TYPE_5__ {TYPE_1__ iq; } ;
struct csio_q {TYPE_2__ un; } ;
struct TYPE_6__ {int type_gen; } ;
struct csio_iqwr_footer {TYPE_3__ u; } ;

/* Variables and functions */
 int IQWRF_GEN_SHIFT ; 

__attribute__((used)) static inline bool
csio_is_new_iqwr(struct csio_q *q, struct csio_iqwr_footer *ftr)
{
	return (q->un.iq.genbit == (ftr->u.type_gen >> IQWRF_GEN_SHIFT));
}