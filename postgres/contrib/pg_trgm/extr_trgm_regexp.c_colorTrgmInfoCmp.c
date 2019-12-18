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
struct TYPE_2__ {int /*<<< orphan*/  ctrgm; } ;
typedef  TYPE_1__ ColorTrgmInfo ;
typedef  int /*<<< orphan*/  ColorTrgm ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
colorTrgmInfoCmp(const void *p1, const void *p2)
{
	const ColorTrgmInfo *c1 = (const ColorTrgmInfo *) p1;
	const ColorTrgmInfo *c2 = (const ColorTrgmInfo *) p2;

	return memcmp(&c1->ctrgm, &c2->ctrgm, sizeof(ColorTrgm));
}