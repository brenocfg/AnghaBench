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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tmp ;
struct cw1200_common {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int cw1200_reg_read (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cw1200_reg_read_32(struct cw1200_common *priv,
				     u16 addr, u32 *val)
{
	__le32 tmp;
	int i = cw1200_reg_read(priv, addr, &tmp, sizeof(tmp));
	*val = le32_to_cpu(tmp);
	return i;
}