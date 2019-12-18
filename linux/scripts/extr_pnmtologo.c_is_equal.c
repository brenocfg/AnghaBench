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
struct color {scalar_t__ red; scalar_t__ green; scalar_t__ blue; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_equal(struct color c1, struct color c2)
{
    return c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue;
}