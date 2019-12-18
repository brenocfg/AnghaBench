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
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 int stbi__get16be (int /*<<< orphan*/ *) ; 
 int stbi__get8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi__rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi__tga_test(stbi__context *s)
{
   int res;
   int sz;
   stbi__get8(s);      //   discard Offset
   sz = stbi__get8(s);   //   color type
   if ( sz > 1 ) return 0;   //   only RGB or indexed allowed
   sz = stbi__get8(s);   //   image type
   if ( (sz != 1) && (sz != 2) && (sz != 3) && (sz != 9) && (sz != 10) && (sz != 11) ) return 0;   //   only RGB or grey allowed, +/- RLE
   stbi__get16be(s);      //   discard palette start
   stbi__get16be(s);      //   discard palette length
   stbi__get8(s);         //   discard bits per palette color entry
   stbi__get16be(s);      //   discard x origin
   stbi__get16be(s);      //   discard y origin
   if ( stbi__get16be(s) < 1 ) return 0;      //   test width
   if ( stbi__get16be(s) < 1 ) return 0;      //   test height
   sz = stbi__get8(s);   //   bits per pixel
   if ( (sz != 8) && (sz != 16) && (sz != 24) && (sz != 32) )
      res = 0;
   else
      res = 1;
   stbi__rewind(s);
   return res;
}