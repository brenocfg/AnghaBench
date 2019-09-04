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
struct TYPE_2__ {int /*<<< orphan*/  s_last_cno; } ;
struct grub_nilfs2_data {TYPE_1__ sblock; } ;
struct grub_nilfs2_checkpoint {int dummy; } ;
typedef  int /*<<< orphan*/  grub_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  grub_le_to_cpu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_nilfs2_read_checkpoint (struct grub_nilfs2_data*,int /*<<< orphan*/ ,struct grub_nilfs2_checkpoint*) ; 

__attribute__((used)) static inline grub_err_t
grub_nilfs2_read_last_checkpoint (struct grub_nilfs2_data *data,
				  struct grub_nilfs2_checkpoint *cpp)
{
  return grub_nilfs2_read_checkpoint (data,
				      grub_le_to_cpu64 (data->
							sblock.s_last_cno),
				      cpp);
}