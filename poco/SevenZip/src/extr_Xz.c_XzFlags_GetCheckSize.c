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
typedef  int /*<<< orphan*/  CXzStreamFlags ;

/* Variables and functions */
 int XzFlags_GetCheckType (int /*<<< orphan*/ ) ; 

unsigned XzFlags_GetCheckSize(CXzStreamFlags f)
{
  int t = XzFlags_GetCheckType(f);
  return (t == 0) ? 0 : (4 << ((t - 1) / 3));
}