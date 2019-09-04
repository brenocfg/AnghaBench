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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  rv ;

/* Variables and functions */
 int /*<<< orphan*/  CDF_TOLE4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static uint32_t
cdf_getuint32(const uint8_t *p, size_t offs)
{
	uint32_t rv;
	(void)memcpy(&rv, p + offs * sizeof(uint32_t), sizeof(rv));
	return CDF_TOLE4(rv);
}