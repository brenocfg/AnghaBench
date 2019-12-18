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

/* Variables and functions */
 int _n ; 
 int /*<<< orphan*/  setnewline (int) ; 

__attribute__((used)) static int up(void *n) {
	int old = _n;
	if (_n > 0) {
		_n--;
	}
	setnewline (old);
	return -1;
}