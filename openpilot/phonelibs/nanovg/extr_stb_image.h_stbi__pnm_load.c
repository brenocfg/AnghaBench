#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stbi_uc ;
struct TYPE_5__ {int img_x; int img_y; int img_n; } ;
typedef  TYPE_1__ stbi__context ;

/* Variables and functions */
 int /*<<< orphan*/ * stbi__convert_format (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * stbi__errpuc (char*,char*) ; 
 int /*<<< orphan*/  stbi__getn (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stbi__malloc (int) ; 
 int /*<<< orphan*/  stbi__pnm_info (TYPE_1__*,int*,int*,int*) ; 

__attribute__((used)) static stbi_uc *stbi__pnm_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
   stbi_uc *out;
   if (!stbi__pnm_info(s, (int *)&s->img_x, (int *)&s->img_y, (int *)&s->img_n))
      return 0;
   *x = s->img_x;
   *y = s->img_y;
   *comp = s->img_n;

   out = (stbi_uc *) stbi__malloc(s->img_n * s->img_x * s->img_y);
   if (!out) return stbi__errpuc("outofmem", "Out of memory");
   stbi__getn(s, out, s->img_n * s->img_x * s->img_y);

   if (req_comp && req_comp != s->img_n) {
      out = stbi__convert_format(out, s->img_n, req_comp, s->img_x, s->img_y);
      if (out == NULL) return out; // stbi__convert_format frees input on failure
   }
   return out;
}