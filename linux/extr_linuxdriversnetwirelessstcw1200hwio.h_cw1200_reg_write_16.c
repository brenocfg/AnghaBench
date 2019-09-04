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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  tmp ;
struct cw1200_common {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int cw1200_reg_write (struct cw1200_common*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int cw1200_reg_write_16(struct cw1200_common *priv,
				      u16 addr, u16 val)
{
	__le32 tmp = cpu_to_le32((u32)val);
	return cw1200_reg_write(priv, addr, &tmp, sizeof(tmp));
}