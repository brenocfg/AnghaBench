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
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int esil_mem_addeq_n (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool esil_mem_addeq2(RAnalEsil *esil) {
	return esil_mem_addeq_n (esil, 16);
}