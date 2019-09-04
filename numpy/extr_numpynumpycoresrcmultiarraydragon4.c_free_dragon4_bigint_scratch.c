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
typedef  int /*<<< orphan*/  Dragon4_Scratch ;

/* Variables and functions */
 scalar_t__ _bigint_static_in_use ; 

__attribute__((used)) static void
free_dragon4_bigint_scratch(Dragon4_Scratch *mem){
    _bigint_static_in_use = 0;
}