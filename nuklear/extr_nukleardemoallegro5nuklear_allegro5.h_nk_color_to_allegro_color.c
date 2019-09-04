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
struct nk_color {scalar_t__ a; scalar_t__ b; scalar_t__ g; scalar_t__ r; } ;
typedef  int /*<<< orphan*/  ALLEGRO_COLOR ;

/* Variables and functions */
 int /*<<< orphan*/  al_map_rgba (unsigned char,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static ALLEGRO_COLOR
nk_color_to_allegro_color(struct nk_color color)
{
    return al_map_rgba((unsigned char)color.r, (unsigned char)color.g,
                (unsigned char)color.b, (unsigned char)color.a);
}