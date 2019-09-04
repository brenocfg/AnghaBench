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
struct be_sge {int dummy; } ;
struct TYPE_2__ {struct be_sge* sgl; } ;
struct be_mcc_wrb {TYPE_1__ payload; } ;

/* Variables and functions */

__attribute__((used)) static inline struct be_sge *nonembedded_sgl(struct be_mcc_wrb *wrb)
{
	return &wrb->payload.sgl[0];
}