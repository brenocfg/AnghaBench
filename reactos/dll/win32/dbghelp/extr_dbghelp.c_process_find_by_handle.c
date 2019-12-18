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
struct process {scalar_t__ handle; struct process* next; } ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 struct process* process_first ; 

struct process*    process_find_by_handle(HANDLE hProcess)
{
    struct process* p;

    for (p = process_first; p && p->handle != hProcess; p = p->next);
    if (!p) SetLastError(ERROR_INVALID_HANDLE);
    return p;
}