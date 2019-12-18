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
typedef  int /*<<< orphan*/  RBinJavaField ;

/* Variables and functions */
 scalar_t__ check_addr_less_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_addr_less_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_addr_in_code (RBinJavaField *method, ut64 addr) {
	return !check_addr_less_start (method, addr) && \
		check_addr_less_end ( method, addr);
}