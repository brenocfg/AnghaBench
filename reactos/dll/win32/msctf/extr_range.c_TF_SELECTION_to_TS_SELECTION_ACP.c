#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  anchorEnd; int /*<<< orphan*/  anchorStart; } ;
struct TYPE_10__ {int /*<<< orphan*/  fInterimChar; int /*<<< orphan*/  ase; } ;
struct TYPE_12__ {TYPE_2__ style; int /*<<< orphan*/  range; } ;
struct TYPE_9__ {int /*<<< orphan*/  fInterimChar; int /*<<< orphan*/  ase; } ;
struct TYPE_11__ {TYPE_1__ style; int /*<<< orphan*/  acpEnd; int /*<<< orphan*/  acpStart; } ;
typedef  TYPE_3__ TS_SELECTION_ACP ;
typedef  TYPE_4__ TF_SELECTION ;
typedef  TYPE_5__ Range ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_5__* impl_from_ITfRange (int /*<<< orphan*/ ) ; 

HRESULT TF_SELECTION_to_TS_SELECTION_ACP(const TF_SELECTION *tf, TS_SELECTION_ACP *tsAcp)
{
    Range *This;

    if (!tf || !tsAcp || !tf->range)
        return E_INVALIDARG;

    This = impl_from_ITfRange(tf->range);

    tsAcp->acpStart = This->anchorStart;
    tsAcp->acpEnd = This->anchorEnd;
    tsAcp->style.ase = tf->style.ase;
    tsAcp->style.fInterimChar = tf->style.fInterimChar;
    return S_OK;
}