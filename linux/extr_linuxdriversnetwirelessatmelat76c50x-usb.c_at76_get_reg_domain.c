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
typedef  scalar_t__ u16 ;
struct reg_domain {int member_0; char* member_1; int member_2; scalar_t__ code; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_domain const*) ; 

__attribute__((used)) static struct reg_domain const *at76_get_reg_domain(u16 code)
{
	int i;
	static struct reg_domain const fd_tab[] = {
		{ 0x10, "FCC (USA)", 0x7ff },	/* ch 1-11 */
		{ 0x20, "IC (Canada)", 0x7ff },	/* ch 1-11 */
		{ 0x30, "ETSI (most of Europe)", 0x1fff },	/* ch 1-13 */
		{ 0x31, "Spain", 0x600 },	/* ch 10-11 */
		{ 0x32, "France", 0x1e00 },	/* ch 10-13 */
		{ 0x40, "MKK (Japan)", 0x2000 },	/* ch 14 */
		{ 0x41, "MKK1 (Japan)", 0x3fff },	/* ch 1-14 */
		{ 0x50, "Israel", 0x3fc },	/* ch 3-9 */
		{ 0x00, "<unknown>", 0xffffffff }	/* ch 1-32 */
	};

	/* Last entry is fallback for unknown domain code */
	for (i = 0; i < ARRAY_SIZE(fd_tab) - 1; i++)
		if (code == fd_tab[i].code)
			break;

	return &fd_tab[i];
}