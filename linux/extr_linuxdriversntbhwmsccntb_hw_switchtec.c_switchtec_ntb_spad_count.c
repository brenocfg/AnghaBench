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
struct switchtec_ntb {TYPE_1__* self_shared; } ;
struct ntb_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  spad; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 

__attribute__((used)) static int switchtec_ntb_spad_count(struct ntb_dev *ntb)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);

	return ARRAY_SIZE(sndev->self_shared->spad);
}