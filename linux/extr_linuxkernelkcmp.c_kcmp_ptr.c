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
typedef  enum kcmp_type { ____Placeholder_kcmp_type } kcmp_type ;

/* Variables and functions */
 long kptr_obfuscate (long,int) ; 

__attribute__((used)) static int kcmp_ptr(void *v1, void *v2, enum kcmp_type type)
{
	long t1, t2;

	t1 = kptr_obfuscate((long)v1, type);
	t2 = kptr_obfuscate((long)v2, type);

	return (t1 < t2) | ((t1 > t2) << 1);
}