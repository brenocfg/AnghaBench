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
typedef  enum ARRAY_TYPE { ____Placeholder_ARRAY_TYPE } ARRAY_TYPE ;

/* Variables and functions */
 int ECPG_ARRAY_ARRAY ; 
 int ECPG_ARRAY_VECTOR ; 

__attribute__((used)) static bool
array_boundary(enum ARRAY_TYPE isarray, char c)
{
	if (isarray == ECPG_ARRAY_ARRAY && c == '}')
		return true;

	if (isarray == ECPG_ARRAY_VECTOR && c == '\0')
		return true;

	return false;
}