#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_5__ {double n; double d; } ;
typedef  TYPE_1__ RNumCalcValue ;
typedef  int /*<<< orphan*/  RNumCalc ;
typedef  int /*<<< orphan*/  RNum ;

/* Variables and functions */
 scalar_t__ IS_DIGIT (char) ; 
 TYPE_1__ Nset (int /*<<< orphan*/ ) ; 
 TYPE_1__ Nsetf (double) ; 
 int R_NUMCALC_STRSZ ; 
 scalar_t__ cin_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cin_putback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  isalnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_num_get (int /*<<< orphan*/ *,char*) ; 
 int sscanf (char*,char*,double*) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static int cin_get_num(RNum *num, RNumCalc *nc, RNumCalcValue *n) {
	double d;
	char str[R_NUMCALC_STRSZ + 1]; // TODO: move into the heap?
	int i = 0;
	char c;
	str[0] = 0;
	while (cin_get (num, nc, &c)) {
		if (c != '_' && c!=':' && c!='.' && !isalnum ((ut8)c)) {
			cin_putback (num, nc, c);
			break;
		}
		if (i < R_NUMCALC_STRSZ) {
			str[i++] = c;
		}
	}
	str[i] = 0;
	*n = Nset (r_num_get (num, str));
	if (IS_DIGIT (*str) && strchr (str, '.')) {
		if (sscanf (str, "%lf", &d) < 1) {
			return 0;
		}
		if (n->n < d) {
			*n = Nsetf (d);
		}
		n->d = d;
	}
	return 1;
}