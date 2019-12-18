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
typedef  int ut32 ;
typedef  int dicti ;
struct TYPE_3__ {int size; } ;
typedef  TYPE_1__ dict ;

/* Variables and functions */

__attribute__((used)) static ut32 dict_bucket(dict *m, dicti k) {
	if (m->size > 0) {
		return k % m->size;
	}
	return 0;
}