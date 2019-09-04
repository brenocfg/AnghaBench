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
typedef  int /*<<< orphan*/  wszUsage ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CharToOemW (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void
usage (void)
{
  WCHAR wszUsage[4096];
  char oemUsage[4096];

  LoadStringW (GetModuleHandleW (NULL), IDS_USAGE, wszUsage, sizeof(wszUsage) / sizeof(wszUsage[0]));
  CharToOemW (wszUsage, oemUsage);
  fputs (oemUsage, stdout);
}