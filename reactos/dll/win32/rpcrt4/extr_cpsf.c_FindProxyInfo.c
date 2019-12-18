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
struct TYPE_4__ {scalar_t__ (* pIIDLookupRtn ) (int /*<<< orphan*/ ,int*) ;} ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_1__ ProxyFileInfo ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static BOOL FindProxyInfo(const ProxyFileInfo **pProxyFileList, REFIID riid, const ProxyFileInfo **pProxyInfo, int *pIndex)
{
  while (*pProxyFileList) {
    if ((*pProxyFileList)->pIIDLookupRtn(riid, pIndex)) {
      *pProxyInfo = *pProxyFileList;
      TRACE("found: ProxyInfo %p Index %d\n", *pProxyInfo, *pIndex);
      return TRUE;
    }
    pProxyFileList++;
  }
  TRACE("not found\n");
  return FALSE;
}