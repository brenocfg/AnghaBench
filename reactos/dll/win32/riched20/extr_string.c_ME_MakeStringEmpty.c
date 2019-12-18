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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int nLen; int nBuffer; scalar_t__* szData; } ;
typedef  TYPE_1__ ME_String ;

/* Variables and functions */
 int ME_GetOptimalBuffer (int) ; 
 scalar_t__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_string_free ; 
 TYPE_1__* make_string (int /*<<< orphan*/ ) ; 

ME_String *ME_MakeStringEmpty(int nMaxChars)
{
  ME_String *s = make_string( heap_string_free );

  if (!s) return NULL;
  s->nLen = nMaxChars;
  s->nBuffer = ME_GetOptimalBuffer(s->nLen + 1);
  s->szData = heap_alloc( s->nBuffer * sizeof(WCHAR) );
  if (!s->szData)
  {
    heap_free( s );
    return NULL;
  }
  s->szData[s->nLen] = 0;
  return s;
}