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
 int stbi__err (char*,char*) ; 
 int stbi__get8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi__check_png_header(stbi__context *s)
{
   static stbi_uc png_sig[8] = { 137,80,78,71,13,10,26,10 };
   int i;
   for (i=0; i < 8; ++i)
      if (stbi__get8(s) != png_sig[i]) return stbi__err("bad png sig","Not a PNG");
   return 1;
}