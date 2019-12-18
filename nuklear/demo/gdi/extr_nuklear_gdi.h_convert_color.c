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
struct nk_color {int r; int g; int b; } ;
typedef  int COLORREF ;

/* Variables and functions */

__attribute__((used)) static COLORREF
convert_color(struct nk_color c)
{
    return c.r | (c.g << 8) | (c.b << 16);
}