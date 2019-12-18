#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* perf; } ;
struct TYPE_4__ {int erfOper; int erfType; int /*<<< orphan*/  fError; } ;
typedef  TYPE_2__ FCI_Int ;

/* Variables and functions */
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void set_error( FCI_Int *fci, int oper, int err )
{
    fci->perf->erfOper = oper;
    fci->perf->erfType = err;
    fci->perf->fError = TRUE;
    if (err) SetLastError( err );
}