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
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_2__ {int /*<<< orphan*/  u32; } ;
typedef  TYPE_1__ unalign ;

/* Variables and functions */

__attribute__((used)) static ut32 LZ4_read32(const void* ptr) { return ((const unalign*)ptr)->u32; }