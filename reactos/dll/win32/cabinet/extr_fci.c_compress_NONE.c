#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cab_UWORD ;
struct TYPE_3__ {int /*<<< orphan*/  cdata_in; int /*<<< orphan*/  data_in; int /*<<< orphan*/  data_out; } ;
typedef  TYPE_1__ FCI_Int ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cab_UWORD compress_NONE( FCI_Int *fci )
{
    memcpy( fci->data_out, fci->data_in, fci->cdata_in );
    return fci->cdata_in;
}