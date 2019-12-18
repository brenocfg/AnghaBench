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
typedef  char* LPSTR ;
typedef  char* LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static LPSTR RPCRT4_strconcatA(LPSTR dst, LPCSTR src)
{
  DWORD len = strlen(dst), slen = strlen(src);
  LPSTR ndst = HeapReAlloc(GetProcessHeap(), 0, dst, (len+slen+2)*sizeof(CHAR));
  if (!ndst)
  {
    HeapFree(GetProcessHeap(), 0, dst);
    return NULL;
  }
  ndst[len] = ',';
  memcpy(ndst+len+1, src, slen+1);
  return ndst;
}