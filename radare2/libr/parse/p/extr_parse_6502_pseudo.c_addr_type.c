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
typedef  int /*<<< orphan*/  ADDR_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  IDX_IND ; 
 int /*<<< orphan*/  IND_IDX ; 
 int /*<<< orphan*/  NORM ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static ADDR_TYPE addr_type(const char *str) {
	if (strchr(str, '(')) {
		char *e = strchr (str, ')');
		if (!e) {
			return NORM;
		}
		char *o = strchr (e, ',');
		return (o) ? IND_IDX : IDX_IND;
	}
	return NORM;
}