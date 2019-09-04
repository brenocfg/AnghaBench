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
struct r8152 {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_ocp_read (struct r8152*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ocp_read_dword(struct r8152 *tp, u16 type, u16 index)
{
	__le32 data;

	generic_ocp_read(tp, index, sizeof(data), &data, type);

	return __le32_to_cpu(data);
}