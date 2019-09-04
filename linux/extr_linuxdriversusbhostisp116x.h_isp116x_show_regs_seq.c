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
struct seq_file {int dummy; } ;
struct isp116x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp116x_show_regs (struct isp116x*,int /*<<< orphan*/ ,struct seq_file*) ; 
 int /*<<< orphan*/  seq ; 

__attribute__((used)) static inline void isp116x_show_regs_seq(struct isp116x *isp116x,
					  struct seq_file *s)
{
	isp116x_show_regs(isp116x, seq, s);
}