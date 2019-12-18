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

__attribute__((used)) static inline ino_t u32_to_ino_t(__u32 uino)
{
	return (ino_t) uino;
}