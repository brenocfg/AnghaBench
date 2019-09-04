#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int curr_tok; } ;
typedef  int /*<<< orphan*/  RNumCalcValue ;
typedef  TYPE_1__ RNumCalc ;
typedef  int /*<<< orphan*/  RNum ;

/* Variables and functions */
 int /*<<< orphan*/  Nadd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Nand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Norr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Nrol (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Nror (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Nshl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Nshr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Nsub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Nxor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  RNCAND 136 
#define  RNCMINUS 135 
#define  RNCORR 134 
#define  RNCPLUS 133 
#define  RNCROL 132 
#define  RNCROR 131 
#define  RNCSHL 130 
#define  RNCSHR 129 
#define  RNCXOR 128 
 int /*<<< orphan*/  term (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static RNumCalcValue expr(RNum *num, RNumCalc *nc, int get) {
	RNumCalcValue left = term (num, nc, get);
	for (;;) {
		switch (nc->curr_tok) {
		case RNCSHL: left = Nshl (left, term (num, nc, 1)); break;
		case RNCSHR: left = Nshr (left, term (num, nc, 1)); break;
		case RNCROL: left = Nrol (left, term (num, nc, 1)); break;
		case RNCROR: left = Nror (left, term (num, nc, 1)); break;
		case RNCPLUS: left = Nadd (left, term (num, nc, 1)); break;
		case RNCMINUS: left = Nsub (left, term (num, nc, 1)); break;
		case RNCXOR: left = Nxor (left, term (num, nc, 1)); break;
		case RNCORR: left = Norr (left, term (num, nc, 1)); break;
		case RNCAND: left = Nand (left, term (num, nc, 1)); break;
		default:
			return left;
		}
	}
	return left;
}