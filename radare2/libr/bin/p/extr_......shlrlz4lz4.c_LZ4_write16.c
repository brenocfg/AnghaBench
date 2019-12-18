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
typedef  int /*<<< orphan*/  ut16 ;
struct TYPE_2__ {int /*<<< orphan*/  u16; } ;
typedef  TYPE_1__ unalign ;

/* Variables and functions */

__attribute__((used)) static void LZ4_write16(void* memPtr, ut16 value) { ((unalign*)memPtr)->u16 = value; }