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

/* Variables and functions */
 scalar_t__ GCR_DATA ; 
 scalar_t__ GCR_INDEX ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline u32 snd_als300_gcr_read(unsigned long port, unsigned short reg)
{
	outb(reg, port+GCR_INDEX);
	return inl(port+GCR_DATA);
}