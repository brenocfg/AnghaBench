#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lfFaceName; } ;
typedef  TYPE_1__ LOGFONTW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (TYPE_1__ const*,TYPE_1__ const*,int) ; 

__attribute__((used)) static BOOL ME_IsFontEqual(const LOGFONTW *p1, const LOGFONTW *p2)
{
  if (memcmp(p1, p2, sizeof(LOGFONTW)-sizeof(p1->lfFaceName)))
    return FALSE;
  if (lstrcmpW(p1->lfFaceName, p2->lfFaceName))
    return FALSE;
  return TRUE;
}