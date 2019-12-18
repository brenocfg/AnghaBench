#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  boundbox; } ;
struct TYPE_4__ {int sk_subtype; int /*<<< orphan*/  sk_argument; int /*<<< orphan*/  sk_strategy; } ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  BOX ;

/* Variables and functions */
#define  BOXOID 129 
 int /*<<< orphan*/ * DatumGetBoxP (int /*<<< orphan*/ ) ; 
 TYPE_3__* DatumGetPolygonP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
#define  POLYGONOID 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  is_bounding_box_test_exact (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOX *
spg_box_quad_get_scankey_bbox(ScanKey sk, bool *recheck)
{
	switch (sk->sk_subtype)
	{
		case BOXOID:
			return DatumGetBoxP(sk->sk_argument);

		case POLYGONOID:
			if (recheck && !is_bounding_box_test_exact(sk->sk_strategy))
				*recheck = true;
			return &DatumGetPolygonP(sk->sk_argument)->boundbox;

		default:
			elog(ERROR, "unrecognized scankey subtype: %d", sk->sk_subtype);
			return NULL;
	}
}