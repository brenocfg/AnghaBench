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
struct rs_rate {scalar_t__ ant; scalar_t__ sgi; scalar_t__ bfer; scalar_t__ stbc; } ;
typedef  enum rs_column { ____Placeholder_rs_column } rs_column ;

/* Variables and functions */
 scalar_t__ ANT_A ; 
 scalar_t__ ANT_B ; 
 int RS_COLUMN_INVALID ; 
 int RS_COLUMN_LEGACY_ANT_A ; 
 int RS_COLUMN_LEGACY_ANT_B ; 
 int RS_COLUMN_MIMO2 ; 
 int RS_COLUMN_MIMO2_SGI ; 
 int RS_COLUMN_SISO_ANT_A ; 
 int RS_COLUMN_SISO_ANT_A_SGI ; 
 int RS_COLUMN_SISO_ANT_B ; 
 int RS_COLUMN_SISO_ANT_B_SGI ; 
 scalar_t__ is_legacy (struct rs_rate*) ; 
 scalar_t__ is_mimo (struct rs_rate*) ; 
 scalar_t__ is_siso (struct rs_rate*) ; 

__attribute__((used)) static inline enum rs_column rs_get_column_from_rate(struct rs_rate *rate)
{
	if (is_legacy(rate)) {
		if (rate->ant == ANT_A)
			return RS_COLUMN_LEGACY_ANT_A;

		if (rate->ant == ANT_B)
			return RS_COLUMN_LEGACY_ANT_B;

		goto err;
	}

	if (is_siso(rate)) {
		if (rate->ant == ANT_A || rate->stbc || rate->bfer)
			return rate->sgi ? RS_COLUMN_SISO_ANT_A_SGI :
				RS_COLUMN_SISO_ANT_A;

		if (rate->ant == ANT_B)
			return rate->sgi ? RS_COLUMN_SISO_ANT_B_SGI :
				RS_COLUMN_SISO_ANT_B;

		goto err;
	}

	if (is_mimo(rate))
		return rate->sgi ? RS_COLUMN_MIMO2_SGI : RS_COLUMN_MIMO2;

err:
	return RS_COLUMN_INVALID;
}