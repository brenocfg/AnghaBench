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
struct TYPE_4__ {int* bitmap; int width; int height; } ;
typedef  TYPE_1__ Wbmp ;

/* Variables and functions */
 int /*<<< orphan*/  gdFree (TYPE_1__*) ; 
 scalar_t__ gdMalloc (int) ; 
 scalar_t__ overflow2 (int,int) ; 
 scalar_t__ safe_emalloc (int,int,int /*<<< orphan*/ ) ; 

Wbmp *
createwbmp (int width, int height, int color)
{
  int i;

  Wbmp *wbmp;
  if ((wbmp = (Wbmp *) gdMalloc (sizeof (Wbmp))) == NULL)
    return (NULL);

  if (overflow2(sizeof (int), width)) {
    gdFree(wbmp);
    return NULL;
  }
  if (overflow2(sizeof (int) * width, height)) {
    gdFree(wbmp);
    return NULL;
  }

  if ((wbmp->bitmap = (int *) safe_emalloc(sizeof(int), width * height, 0)) == NULL)
    {
      gdFree (wbmp);
      return (NULL);
    }

  wbmp->width = width;
  wbmp->height = height;

  for (i = 0; i < width * height; wbmp->bitmap[i++] = color);

  return (wbmp);
}