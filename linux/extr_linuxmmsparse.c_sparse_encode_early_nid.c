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

/* Variables and functions */
 int SECTION_NID_SHIFT ; 

__attribute__((used)) static inline unsigned long sparse_encode_early_nid(int nid)
{
	return (nid << SECTION_NID_SHIFT);
}