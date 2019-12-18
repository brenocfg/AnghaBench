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
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  CompareFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

LONG MONTHCAL_CompareSystemTime(const SYSTEMTIME *first, const SYSTEMTIME *second)
{
  FILETIME ft_first, ft_second;

  SystemTimeToFileTime(first, &ft_first);
  SystemTimeToFileTime(second, &ft_second);

  return CompareFileTime(&ft_first, &ft_second);
}