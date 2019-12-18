#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct Ziphuft* t; } ;
struct Ziphuft {TYPE_1__ v; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (struct Ziphuft*) ;} ;
typedef  TYPE_2__ FDI_Int ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct Ziphuft*) ; 

__attribute__((used)) static void fdi_Ziphuft_free(FDI_Int *fdi, struct Ziphuft *t)
{
  register struct Ziphuft *p, *q;

  /* Go through linked list, freeing from the allocated (t[-1]) address. */
  p = t;
  while (p != NULL)
  {
    q = (--p)->v.t;
    fdi->free(p);
    p = q;
  } 
}