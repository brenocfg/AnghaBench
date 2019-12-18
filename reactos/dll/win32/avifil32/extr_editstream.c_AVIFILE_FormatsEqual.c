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
typedef  int /*<<< orphan*/ * PAVISTREAM ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  scalar_t__ LONG ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AVIStreamFormatSize (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  AVIStreamReadFormat (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ AVIStreamStart (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static BOOL AVIFILE_FormatsEqual(PAVISTREAM avi1, PAVISTREAM avi2)
{
  LPVOID fmt1 = NULL, fmt2 = NULL;
  LONG size1, size2, start1, start2;
  BOOL status = FALSE;

  assert(avi1 != NULL && avi2 != NULL);

  /* get stream starts and check format sizes */
  start1 = AVIStreamStart(avi1);
  start2 = AVIStreamStart(avi2);
  if (FAILED(AVIStreamFormatSize(avi1, start1, &size1)))
    return FALSE;
  if (FAILED(AVIStreamFormatSize(avi2, start2, &size2)))
    return FALSE;
  if (size1 != size2)
    return FALSE;

  /* sizes match, now get formats and compare them */
  fmt1 = HeapAlloc(GetProcessHeap(), 0, size1);
  if (fmt1 == NULL)
    return FALSE;
  if (SUCCEEDED(AVIStreamReadFormat(avi1, start1, fmt1, &size1))) {
    fmt2 = HeapAlloc(GetProcessHeap(), 0, size1);
    if (fmt2 != NULL) {
      if (SUCCEEDED(AVIStreamReadFormat(avi2, start2, fmt2, &size1)))
        status = (memcmp(fmt1, fmt2, size1) == 0);
    }
  }

  HeapFree(GetProcessHeap(), 0, fmt2);
  HeapFree(GetProcessHeap(), 0, fmt1);

  return status;
}