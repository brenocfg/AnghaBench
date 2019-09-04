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
struct TYPE_2__ {int ksft_xskip; } ;

/* Variables and functions */
 TYPE_1__ ksft_cnt ; 

__attribute__((used)) static inline int ksft_get_xskip_cnt(void) { return ksft_cnt.ksft_xskip; }