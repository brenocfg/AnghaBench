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
typedef  int /*<<< orphan*/  pcre_uint8 ;
typedef  int pcre_uint32 ;
typedef  int /*<<< orphan*/  pcre_uchar ;
typedef  int /*<<< orphan*/  compile_data ;
typedef  int BOOL ;

/* Variables and functions */
 int const NOTACHAR ; 
 int PCRE_UTF8 ; 
 scalar_t__ add_to_class (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int const,int const) ; 

__attribute__((used)) static int
add_not_list_to_class(pcre_uint8 *classbits, pcre_uchar **uchardptr,
  int options, compile_data *cd, const pcre_uint32 *p)
{
BOOL utf = (options & PCRE_UTF8) != 0;
int n8 = 0;
if (p[0] > 0)
  n8 += add_to_class(classbits, uchardptr, options, cd, 0, p[0] - 1);
while (p[0] < NOTACHAR)
  {
  while (p[1] == p[0] + 1) p++;
  n8 += add_to_class(classbits, uchardptr, options, cd, p[0] + 1,
    (p[1] == NOTACHAR) ? (utf ? 0x10ffffu : 0xffffffffu) : p[1] - 1);
  p++;
  }
return n8;
}