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
struct CPRBX {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  memzero_explicit (void*,int) ; 

__attribute__((used)) static void free_cprbmem(void *mem, size_t paramblen, int scrub)
{
	if (scrub)
		memzero_explicit(mem, 2 * (sizeof(struct CPRBX) + paramblen));
	kfree(mem);
}