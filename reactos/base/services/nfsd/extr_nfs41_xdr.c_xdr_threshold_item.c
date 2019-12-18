#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * hints; scalar_t__ type; } ;
typedef  TYPE_1__ threshold_item4 ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_6__ {int* arr; scalar_t__ count; } ;
typedef  TYPE_2__ bitmap4 ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_bitmap4 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bool_t xdr_threshold_item(
    XDR *xdr,
    threshold_item4 *item)
{
    bitmap4 bitmap;

    if (!xdr_u_int32_t(xdr, &item->type))
        return FALSE;

    if (!xdr_bitmap4(xdr, &bitmap))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &bitmap.count))
        return FALSE;

    if (bitmap.count) {
        if (bitmap.arr[0] & 0x1 && !xdr_u_hyper(xdr, &item->hints[0]))
            return FALSE;
        if (bitmap.arr[0] & 0x2 && !xdr_u_hyper(xdr, &item->hints[1]))
            return FALSE;
        if (bitmap.arr[0] & 0x4 && !xdr_u_hyper(xdr, &item->hints[2]))
            return FALSE;
        if (bitmap.arr[0] & 0x8 && !xdr_u_hyper(xdr, &item->hints[3]))
            return FALSE;
    }
    return TRUE;
}