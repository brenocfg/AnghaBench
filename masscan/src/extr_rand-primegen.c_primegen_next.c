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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {size_t num; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ primegen ;

/* Variables and functions */
 int /*<<< orphan*/  primegen_fill (TYPE_1__*) ; 

uint64_t primegen_next(primegen *pg)
{
  while (!pg->num)
    primegen_fill(pg);

  return pg->p[--pg->num];
}