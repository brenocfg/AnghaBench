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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void output_utf8(luaL_Buffer *buf, int c) {
  char space[4];
  char *b = space;

  if (c<0x80) *b++=c;
  else if (c<0x800) *b++=192+c/64, *b++=128+c%64;
  else if (c-0xd800u<0x800) *b++ = '?';
  else if (c<0x10000) *b++=224+c/4096, *b++=128+c/64%64, *b++=128+c%64;
  else if (c<0x110000) *b++=240+c/262144, *b++=128+c/4096%64, *b++=128+c/64%64, *b++=128+c%64;
  else *b++ = '?';

  luaL_addlstring(buf, space, b - space);
}