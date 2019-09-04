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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_BUFFER_SIZE ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  UNICODE_NULL ; 

VOID
PrintPadding(
    WCHAR chr,
    INT nPaddedLength)
{
    INT i;
    WCHAR szMsgBuffer[MAX_BUFFER_SIZE];

    for (i = 0; i < nPaddedLength; i++)
         szMsgBuffer[i] = chr;
    szMsgBuffer[nPaddedLength] = UNICODE_NULL;

    ConPuts(StdOut, szMsgBuffer);
}