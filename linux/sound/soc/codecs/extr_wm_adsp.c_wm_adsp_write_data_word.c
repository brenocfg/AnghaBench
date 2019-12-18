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
typedef  int u32 ;
struct wm_adsp_region {int dummy; } ;
struct wm_adsp {int /*<<< orphan*/  regmap; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {unsigned int (* region_to_reg ) (struct wm_adsp_region const*,unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int cpu_to_be32 (int) ; 
 int regmap_raw_write (int /*<<< orphan*/ ,unsigned int,int*,int) ; 
 unsigned int stub1 (struct wm_adsp_region const*,unsigned int) ; 
 struct wm_adsp_region* wm_adsp_find_region (struct wm_adsp*,int) ; 

__attribute__((used)) static int wm_adsp_write_data_word(struct wm_adsp *dsp, int mem_type,
				   unsigned int mem_addr, u32 data)
{
	struct wm_adsp_region const *mem = wm_adsp_find_region(dsp, mem_type);
	unsigned int reg;

	if (!mem)
		return -EINVAL;

	reg = dsp->ops->region_to_reg(mem, mem_addr);

	data = cpu_to_be32(data & 0x00ffffffu);

	return regmap_raw_write(dsp->regmap, reg, &data, sizeof(data));
}