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
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 scalar_t__ IS_DIGIT (char const) ; 
 scalar_t__ r_num_get (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bool isnum(RAnalEsil *esil, const char *str, ut64 *num) {
	if (!esil || !str) {
		return false;
	}
	if (IS_DIGIT (*str)) {
		if (num) {
			*num = r_num_get (NULL, str);
		}
		return true;
	}
	if (num) {
		*num = 0;
	}
	return false;
}