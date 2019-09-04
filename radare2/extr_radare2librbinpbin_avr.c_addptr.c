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
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  addsym (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rjmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rjmp_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_fmt (char*,char const*) ; 

__attribute__((used)) static void addptr(RList *ret, const char *name, ut64 addr, RBuffer *b) {
	if (b && rjmp (b, 0)) {
		addsym (ret, sdb_fmt ("vector.%s", name), addr);
		ut64 ptr_addr = rjmp_dest (addr, b);
		addsym (ret, sdb_fmt ("syscall.%s", name), ptr_addr);
	}
}