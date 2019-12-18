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
struct TYPE_4__ {int nLen; scalar_t__ nBuffer; int /*<<< orphan*/ * szData; } ;
typedef  TYPE_1__ ME_String ;

/* Variables and functions */
 TYPE_1__* make_string (int /*<<< orphan*/ *) ; 

ME_String *ME_MakeStringConst(const WCHAR *str, int len)
{
  ME_String *s = make_string( NULL );
  if (!s) return NULL;

  s->szData = (WCHAR *)str;
  s->nLen = len;
  s->nBuffer = 0;
  return s;
}