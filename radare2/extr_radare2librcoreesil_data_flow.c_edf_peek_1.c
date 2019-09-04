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
 int edf_consume_1_push_1 (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int edf_peek_1 (RAnalEsil *esil) {
	return edf_consume_1_push_1 (esil, "[1]");
}