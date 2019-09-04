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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MT_WCID_ATTR_BASE ; 
 int N_WCIDS ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mt7601u_burst_write_regs (struct mt7601u_dev*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mt7601u_init_wcid_attr_mem(struct mt7601u_dev *dev)
{
	u32 *vals;
	int i, ret;

	vals = kmalloc(sizeof(*vals) * N_WCIDS * 2, GFP_KERNEL);
	if (!vals)
		return -ENOMEM;

	for (i = 0; i < N_WCIDS * 2; i++)
		vals[i] = 1;

	ret = mt7601u_burst_write_regs(dev, MT_WCID_ATTR_BASE,
				       vals, N_WCIDS * 2);
	kfree(vals);

	return ret;
}