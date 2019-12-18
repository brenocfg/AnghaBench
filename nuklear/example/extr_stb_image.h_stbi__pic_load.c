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
typedef  int /*<<< orphan*/  stbi_uc ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ stbi__at_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stbi__convert_format (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * stbi__errpuc (char*,char*) ; 
 int stbi__get16be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi__get32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi__get8 (int /*<<< orphan*/ *) ; 
 scalar_t__ stbi__malloc (int) ; 
 int /*<<< orphan*/  stbi__pic_load_core (int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static stbi_uc *stbi__pic_load(stbi__context *s,int *px,int *py,int *comp,int req_comp)
{
   stbi_uc *result;
   int i, x,y;

   for (i=0; i<92; ++i)
      stbi__get8(s);

   x = stbi__get16be(s);
   y = stbi__get16be(s);
   if (stbi__at_eof(s))  return stbi__errpuc("bad file","file too short (pic header)");
   if ((1 << 28) / x < y) return stbi__errpuc("too large", "Image too large to decode");

   stbi__get32be(s); //skip `ratio'
   stbi__get16be(s); //skip `fields'
   stbi__get16be(s); //skip `pad'

   // intermediate buffer is RGBA
   result = (stbi_uc *) stbi__malloc(x*y*4);
   memset(result, 0xff, x*y*4);

   if (!stbi__pic_load_core(s,x,y,comp, result)) {
      STBI_FREE(result);
      result=0;
   }
   *px = x;
   *py = y;
   if (req_comp == 0) req_comp = *comp;
   result=stbi__convert_format(result,4,req_comp,x,y);

   return result;
}