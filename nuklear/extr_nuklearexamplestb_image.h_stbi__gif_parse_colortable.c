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
typedef  int stbi_uc ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 int stbi__get8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stbi__gif_parse_colortable(stbi__context *s, stbi_uc pal[256][4], int num_entries, int transp)
{
   int i;
   for (i=0; i < num_entries; ++i) {
      pal[i][2] = stbi__get8(s);
      pal[i][1] = stbi__get8(s);
      pal[i][0] = stbi__get8(s);
      pal[i][3] = transp == i ? 0 : 255;
   }
}