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
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int isregornum (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 char* r_anal_esil_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool popRN(RAnalEsil *esil, ut64 *n) {
	char *str = r_anal_esil_pop (esil);
	if (str) {
		bool ret = isregornum (esil, str, n);
		free (str);
		return ret;
	}
	return false;
}