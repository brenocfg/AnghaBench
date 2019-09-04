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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tmp ;
struct cw1200_common {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int __cw1200_reg_write (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __cw1200_reg_write_16(struct cw1200_common *priv,
					u16 addr, u16 val)
{
	__le16 tmp = cpu_to_le16(val);
	return __cw1200_reg_write(priv, addr, &tmp, sizeof(tmp), 0);
}