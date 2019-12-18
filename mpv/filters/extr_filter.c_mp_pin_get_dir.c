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
struct mp_pin {int dir; } ;
typedef  enum mp_pin_dir { ____Placeholder_mp_pin_dir } mp_pin_dir ;

/* Variables and functions */

enum mp_pin_dir mp_pin_get_dir(struct mp_pin *p)
{
    return p->dir;
}