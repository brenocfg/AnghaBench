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
struct TYPE_2__ {int /*<<< orphan*/  user; } ;
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int i8051_is_init ; 
 TYPE_1__ ocbs ; 

__attribute__((used)) static int esil_i8051_fini (RAnalEsil *esil) {
	if (!i8051_is_init) {
		return false;
	}
	R_FREE (ocbs.user);
	i8051_is_init = false;
	return true;
}