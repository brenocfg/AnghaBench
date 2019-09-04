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
 unsigned int const* db_scale_4bit ; 
 unsigned int const* db_scale_5bit ; 
 unsigned int const* db_scale_6bit ; 

__attribute__((used)) static const unsigned int *find_db_scale(unsigned int maxval)
{
	switch (maxval) {
	case 0x0f: return db_scale_4bit;
	case 0x1f: return db_scale_5bit;
	case 0x3f: return db_scale_6bit;
	}
	return NULL;
}