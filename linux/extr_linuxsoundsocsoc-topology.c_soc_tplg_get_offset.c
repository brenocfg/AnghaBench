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
struct soc_tplg {TYPE_1__* fw; scalar_t__ pos; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long soc_tplg_get_offset(struct soc_tplg *tplg)
{
	return (unsigned long)(tplg->pos - tplg->fw->data);
}