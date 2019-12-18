#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/ * szData; } ;
typedef  TYPE_1__ ME_String ;

/* Variables and functions */
 TYPE_1__* ME_MakeStringEmpty (int) ; 

ME_String *ME_MakeStringR(WCHAR cRepeat, int nMaxChars)
{
  int i;
  ME_String *s = ME_MakeStringEmpty(nMaxChars);

  if (!s) return NULL;
  for (i = 0; i < nMaxChars; i++)
    s->szData[i] = cRepeat;
  return s;
}