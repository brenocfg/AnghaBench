#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  fn; } ;
struct bitfield_fetch_param {TYPE_1__ orig; } ;

/* Variables and functions */
 scalar_t__ CHECK_FETCH_FUNCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deref ; 
 int /*<<< orphan*/  free_deref_fetch_param (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_symbol_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bitfield_fetch_param*) ; 
 int /*<<< orphan*/  symbol ; 

__attribute__((used)) static void
free_bitfield_fetch_param(struct bitfield_fetch_param *data)
{
	/*
	 * Don't check the bitfield itself, because this must be the
	 * last fetch function.
	 */
	if (CHECK_FETCH_FUNCS(deref, data->orig.fn))
		free_deref_fetch_param(data->orig.data);
	else if (CHECK_FETCH_FUNCS(symbol, data->orig.fn))
		free_symbol_cache(data->orig.data);

	kfree(data);
}