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
struct snd_hwdep {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ enable_hpi_hwdep ; 

__attribute__((used)) static int snd_asihpi_hpi_open(struct snd_hwdep *hw, struct file *file)
{
	if (enable_hpi_hwdep)
		return 0;
	else
		return -ENODEV;

}