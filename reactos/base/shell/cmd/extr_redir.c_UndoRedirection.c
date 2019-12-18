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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  OldHandle; int /*<<< orphan*/  Number; struct TYPE_4__* Next; } ;
typedef  TYPE_1__ REDIRECTION ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
UndoRedirection(REDIRECTION *Redir, REDIRECTION *End)
{
    for (; Redir != End; Redir = Redir->Next)
    {
        CloseHandle(GetHandle(Redir->Number));
        SetHandle(Redir->Number, Redir->OldHandle);
        Redir->OldHandle = INVALID_HANDLE_VALUE;
    }
}