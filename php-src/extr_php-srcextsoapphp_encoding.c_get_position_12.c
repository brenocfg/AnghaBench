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
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* safe_emalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int* get_position_12(int dimension, const char* str)
{
	int *pos;
	int i = -1, flag = 0;

	pos = safe_emalloc(sizeof(int), dimension, 0);
	memset(pos,0,sizeof(int)*dimension);
	while (*str != '\0' && (*str < '0' || *str > '9') && (*str != '*')) {
		str++;
	}
	if (*str == '*') {
		str++;
		i++;
	}
	while (*str != '\0') {
		if (*str >= '0' && *str <= '9') {
			if (flag == 0) {
				i++;
				flag = 1;
			}
			pos[i] = (pos[i]*10)+(*str-'0');
		} else if (*str == '*') {
			soap_error0(E_ERROR, "Encoding: '*' may only be first arraySize value in list");
		} else {
		  flag = 0;
		}
		str++;
	}
	return pos;
}