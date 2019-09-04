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
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

__attribute__((used)) static inline __u32 ino_t_to_u32(ino_t ino)
{
	return (__u32) ino;
}