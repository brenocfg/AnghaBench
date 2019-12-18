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
typedef  int /*<<< orphan*/  ut64 ;

/* Variables and functions */
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,void*,int) ; 

__attribute__((used)) static int debug_os_read_at(int fdn, void *buf, int sz, ut64 addr) {
	if (lseek (fdn, addr, 0) < 0) {
		return -1;
	}
	return read (fdn, buf, sz);
}