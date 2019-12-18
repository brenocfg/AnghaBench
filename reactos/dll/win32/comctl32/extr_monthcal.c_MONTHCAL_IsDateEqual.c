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
struct TYPE_4__ {scalar_t__ wYear; scalar_t__ wMonth; scalar_t__ wDay; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL MONTHCAL_IsDateEqual(const SYSTEMTIME *first, const SYSTEMTIME *second)
{
  return (first->wYear == second->wYear) && (first->wMonth == second->wMonth) &&
         (first->wDay  == second->wDay);
}